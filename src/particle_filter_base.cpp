#include "particle_filter_base.h"


Eigen::Vector3d
Particle_filter_base::getEstPose() const {
	return est_pose_ ;
} /* End of getEstPose */


Eigen::MatrixXd
Particle_filter_base::getCovariance() const {
	return cov_ ;
} /* End of getCovariance */

