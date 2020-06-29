#ifndef _FAST_SLAM_1_H_
#define _FAST_SLAM_1_H_

#include <cmath>

#include "particle_filter_base.h"
#include "measurement_model.h"
#include "math_utils.h"
#include "low_variance_sampling.h"

class FastSlam_1 : public Particle_filter_base {
  public:
  	FastSlam_1(const int& numParticles) ;

  	void execute( ParticleSet& particles
  				, const Sensor_record& sensorRecord
  				, const Eigen::Vector3d& noise ) ;

  private:
  	Math_utils math_ ;

  	void predict(ParticleSet& particles, const Odometry& odom, const Eigen::Vector3d& noise) ;
  	void correct(ParticleSet& particles, const Observations& observations) ;
  	void resample(ParticleSet& particles) ;
} ; /* End of class */

#endif /* _FAST_SLAM_1_H_ */