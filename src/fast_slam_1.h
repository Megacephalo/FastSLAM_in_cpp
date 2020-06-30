#ifndef _FAST_SLAM_1_H_
#define _FAST_SLAM_1_H_

#include <cmath>
#include <memory>

#include "particle_filter_base.h"
#include "measurement_model.h"
#include "math_utils.h"
#include "low_variance_sampling.h"

class FastSlam_1 : public Particle_filter_base {
  public:
  	FastSlam_1(const int& numParticles) ;

  	ParticleSetPtr execute( ParticleSetPtr& particlesPtr
                  				, const Sensor_record& sensorRecord
                  				, const Eigen::Vector3d& noise ) ;

  private:
  	Math_utils math_ ;
    ParticleSetPtr particles_ ;

  	ParticleSetPtr predict(ParticleSetPtr& particlesPtr, const Odometry& odom, const Eigen::Vector3d& noise) ;
  	ParticleSetPtr correct(ParticleSetPtr& particlesPtr, const Observations& observations) ;
  	ParticleSetPtr resample(ParticleSetPtr& particlesPtr) ;

    void get_most_likely_paritcle(const ParticleSetPtr& particlesPtr) ; //!< Update est_pose_ and cov_ from particle of maximum weight
} ; /* End of class */

#endif /* _FAST_SLAM_1_H_ */