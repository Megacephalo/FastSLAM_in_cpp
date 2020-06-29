#include "measurement_model.h"

Measurement_model::Measurement_model(const Particle& particle, const Observation_model& obs) 
: h_( Eigen::Vector2d::Zero(2) )
, H_( Eigen::Matrix2d::Zero(2, 2) )
{
	calc_exp_z(particle, obs) ;
} /* End of copy constructor */

void
Measurement_model::calc_exp_z(const Particle& particle, const Observation_model& obs) {
	int landmarkID = obs.id ;
	Eigen::Vector3d pose = particle.state ;

	// use the current state of the particle to predict the measurment
	Eigen::Vector2d landmarkPos = particle.landmarks.at( landmarkID - 1).mu ;
	double landm_x = (double)landmarkPos(0) ;
	double landm_y = (double)landmarkPos(1) ;
	double diff_x = landm_x - pose(0) ;
	double diff_y = landm_y - pose(1) ;
	double expectedRange = std::sqrt( std::pow(diff_x, 2) + std::pow( diff_y , 2) ) ;
	double expectedBearing = math_.normalize_angle( std::atan2( diff_y, diff_x ) - pose(2) ) ;

	h_ = Eigen::Vector2d::Zero(2) ;
	h_ << expectedRange, expectedBearing ;

	// Compute the Jacobian H of the measurement function h wrt the landmark location
	H_ = Eigen::Matrix2d::Zero(2, 2) ;
	H_(0, 0) = diff_x / expectedRange ;
	H_(0, 1) = diff_y / expectedRange ;
	H_(1, 0) = ( particle.state(1) - landm_y ) / std::pow( expectedRange, 2) ;
	H_(1, 1) = diff_x / std::pow( expectedRange, 2 ) ;
} /* calc_exp_z */

Measurement_model&
Measurement_model::operator = ( const Measurement_model& new_obs ) {
	h_ = new_obs.h() ;
	H_ = new_obs.H() ;

	return *this ;
} /* End of assignment operator overloading */

Eigen::Vector2d
Measurement_model::h() const {
	return h_ ;
}

Eigen::Matrix2d
Measurement_model::H() const {
	return H_ ;
}