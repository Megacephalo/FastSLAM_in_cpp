#include "pf_slam.h"

PF_SLAM::PF_SLAM( const std::string& sensor_data_file
				, const std::string& map_data_file
				, const bool& visualize
				, const bool& save_frames
				, const int& numParticles
				, const PF_SLAM_Type& pfSlam_type)
: visualize_(visualize)
, save_frames_(save_frames)
{

	sensor_import_.import_from(sensor_data_file) ;	
	all_sensor_records_ = sensor_import_.get() ;

	map_import_.import_from(map_data_file) ;
	landmarks_ = map_import_.landmarks() ;
	int numLandmarks = map_import_.landmark_size() ;

	switch(pfSlam_type) {
		case FAST_SLAM_1:
			fastSlam_ = 
				std::unique_ptr<Particle_filter_base>( new FastSlam_1(numParticles) ) ;
			break ;
	}

	noises_ << 0.005 , 0.01, 0.005 ;

	// // initialize the particles array
	particles_ = ParticleSetPtr( new ParticleSet( numParticles ) ) ;

	ParticleSet::iterator particleIt ;
	for (particleIt = particles_->begin() ; particleIt != particles_->end() ; particleIt++) {
		particleIt->weight = 1. / numParticles ;
		particleIt->history.clear() ;

		for ( int landmIdx = 0 ; landmIdx < numLandmarks ; landmIdx++ ) {
			particleIt->landmarks.push_back( Landmark() ) ;
		}
	}
} /* End of constructor */

void
PF_SLAM::run() {
	for (auto sensor_record : all_sensor_records_) {
		std::string timestamp_msg = "timestamp: " + std::to_string( sensor_record.odom.timestamp ) ;
		std::cout << timestamp_msg << std::endl ;

		// Perform the prediction, correction, and resample step of the particle filter
		particles_ = fastSlam_->execute(particles_, sensor_record, noises_) ;

		if (visualize_) {
			Eigen::VectorXd mu = fastSlam_->getEstPose() ;
			Eigen::MatrixXd sigma = fastSlam_->getCovariance() ;
			Particle most_likely = fastSlam_->most_likely() ;
			drawer_.Plot_state( particles_
							  , mu
							  , sigma
							  , most_likely
							  , landmarks_ 
							  , all_sensor_records_
							  , timestamp_msg) ;
		}

		if (save_frames_) {
			std::stringstream ss ;
			ss << std::setfill('0') << std::setw(3) << sensor_record.odom.timestamp ;
			drawer_.Save("../images/" + ss.str()) ;
		}
	} /* End of for loop */

	std::cout << "Reached the end of the data!\n" ;

	if (visualize_) {
		drawer_.Show() ;	
	}
	
} /* End of run */