#include "fast_slam_1.h"

FastSlam_1::FastSlam_1(const int& numParticles)
: Particle_filter_base(numParticles)
{} /* End of default constructor */

void
FastSlam_1::execute( ParticleSet& particles
	  				, const Sensor_record& sensorRecord
	  				, const Eigen::Vector3d& noise ) {
	predict(particles, sensorRecord.odom, noise) ;
	correct(particles, sensorRecord.observations) ;

	resample(particles) ;
} /* End of execute */


void
FastSlam_1::predict(ParticleSet& particles, const Odometry& odom, const Eigen::Vector3d& noise) {
	double r1_noise = noise(0) ;
	double trans_noise = noise(1) ;
	double r2_noise = noise(2) ;

	for (auto particle : particles) {
		// Append the old position to the history of the particle
		particle.history.push_back( particle.state ) ;

		// Sample a new pose for the particle
		double r1 = math_.normrnd(odom.r1, r1_noise) ;
		double r2 = math_.normrnd(odom.r2, r2_noise) ;
		double trans = math_.normrnd( odom.timestamp, trans_noise ) ;

		double prev_angle = particle.state(3) ;
		particle.state(0) += trans * std::cos( prev_angle + r1 ) ;
		particle.state(1) += trans * std::sin( prev_angle + r1 ) ;
		particle.state(2) = math_.normalize_angle( prev_angle + r1 + r2 ) ;
	}
} /* End of predict */

void
FastSlam_1::correct(ParticleSet& particles, const Observations& observations) {
	// Construct the sensor noise matrix Q_t (2 x 2)
	Eigen::Matrix2d Q_t = 0.01 * Eigen::Matrix2d::Identity(2, 2) ;

	// process each particle
	for (auto particle : particles) {
		Eigen::Vector3d pose = particle.state ;

		// process each measurement
		for (auto obs : observations) {
			long long landmID = obs.id - 1 ; // since we count from 1 and the computers from 0, the index needs to be adjusted

			Measurement_model z_model(particle, obs) ;

			// if the landmark has not been seen before
			if ( !particle.landmarks.at(landmID).observed ) {
				// Initialize its position based on the measurement and the current robot pose:
				particle.landmarks.at(landmID).mu << 	pose(0) + obs.range * std::cos( obs.bearing + pose(2) ) ,
														pose(0) + obs.range * std::sin( obs.bearing + pose(2) ) ;
				
				// Get the Jacobian with respect to the landmark position
				Eigen::Matrix2d obsJacobian = z_model.H() ;

				// Initialize the EKF for this landmark
				Eigen::Matrix2d invH = obsJacobian.inverse() ;
				particle.landmarks.at(landmID).sigma = invH * Q_t * invH.transpose() ;

				// Indicate that this landmark has been observed
				particle.landmarks.at(landmID).observed = true ;
			}
			else {
				// Get the expected measurement
				Eigen::Vector2d expectedZ = z_model.h() ;
				Eigen::Matrix2d obsJacobian = z_model.H() ;
				Eigen::Matrix2d landm_sigma = particle.landmarks.at(landmID).sigma ;

				// Compute the measurement covariance Q
				Eigen::Matrix2d z_cov = obsJacobian * landm_sigma * obsJacobian.transpose() + Q_t ;

				// Calculate the Kalman gain
				Eigen::Matrix2d KalmanGain = landm_sigma * obsJacobian.transpose() * z_cov.inverse() ;

				// Compute the error between the z and expectedZ (remember to normalize the angle)
				Eigen::Vector2d z_diff = Eigen::Vector2d::Zero(2) ;
				z_diff << 	obs.range - expectedZ(0) 							,
							math_.normalize_angle( obs.bearing - expectedZ(1) ) ;

				// Update the mean and covariance of the EKF for this landmark
				particle.landmarks.at(landmID).mu += KalmanGain * z_diff ;
				particle.landmarks.at(landmID).sigma = landm_sigma - KalmanGain * obsJacobian * landm_sigma ;

				// Compute the likelihood of this observation, multiply with the former weigh to account for observing several features in one time step 
				particle.weight *= 1 / std::sqrt( ( 2 * M_PI * z_cov ).determinant() ) * std::exp( -0.5 * z_diff.transpose() * z_cov.inverse() * z_diff ) ;
			}
		} /* for each measurement */
	} /* for each particle */
} /* End of correct */


void
FastSlam_1::resample(ParticleSet& particles) {
	double weight_sum = 0. ;
	double sum_of_squared_weights = 0. ;
	std::vector<double> weights ;
	for (ParticleSet::iterator particle = particles.begin() ; particle != particles.end() ; particle++) {
		weights.push_back( particle->weight ) ;
		weight_sum += (double)particle->weight ;
		sum_of_squared_weights += std::pow((double)particle->weight, 2) ;
	}

	// Normalize the weights
	for (std::vector<double>::iterator weight = weights.begin() ; weight != weights.end() ; weight++) {
		*weight /= weight_sum ;
	}

	// consdier number of effective particles to decide whether to resample or not
	int numParticles = particles.size() ;
	bool useNeff = false ;
	if ( useNeff ) {
		double neff = 1. / sum_of_squared_weights ;
		if (neff > 0.5 * numParticles ) {
			// All particles' attributes remain the same
			// excpet for each particle's weight. It needs to be updated
			for (int i = 0 ; i < numParticles ; i++) {
				particles.at(i).weight = weights.at(i) ;
			}
		}
	}

	/* implement the low variance re-sampling */

	// The cumulative sum
	std::vector<double> cumSum = math_.cumsum(weights) ;
	double weightSum = cumSum.back() ;

	// initialize the step and the current position on the roulette wheel
	double step = weightSum / numParticles ;
	double position = math_.unifrnd(0, weightSum) ;
	int idx = 1 ;

	// walk along the wheel to select the particles
	for ( ParticleSet::iterator particle = particles.begin() 
		; particle != particles.end() 
		; particle++ ) {
		position += step ;
		if (position > weightSum) {
			position -= weightSum ;
			idx = 1 ;
		}

		while( position > cumSum.at(idx) ) {
			idx ++ ;
		}

		*particle = particles.at(idx) ;
		particle->weight = 1 / numParticles ;
	}
} /* End of resample */
