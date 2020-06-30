#include "particle_filter_base.h"


Eigen::Vector3d
Particle_filter_base::getEstPose() const {
	return est_pose_ ;
} /* End of getEstPose */


Eigen::MatrixXd
Particle_filter_base::getCovariance() const {
	return cov_ ;
} /* End of getCovariance */

Particle
Particle_filter_base::most_likely() const {
	return most_likely_ ;
} /* End of most_likely */