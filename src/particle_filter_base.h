#ifndef _PARTICLE_FILTER_BASE_H_
#define _PARTICLE_FILTER_BASE_H_

#include <memory>
#include <Eigen/Dense>

#include "odometry.h"
#include "particle.h"
#include "sensor_record.h"
#include "common_typedefs.h"

class Particle_filter_base {
  public:
    Particle_filter_base(const int& numParticles)
    : numParticles_(numParticles)
    {} /* End of default constructor */

    virtual ~Particle_filter_base()
    {} /* End of virtual destructor */

  	virtual void execute( ParticleSet& particles
          		  				, const Sensor_record& sensorRecord
          		  				, const Eigen::Vector3d& noise ) = 0 ;

  	Eigen::Vector3d getEstPose() const ;
  	Eigen::MatrixXd getCovariance() const ;

  protected:
    int numParticles_ ;  //!< This memeber will be internally referred
  	Eigen::Vector3d est_pose_ ;
  	Eigen::MatrixXd cov_ ;
} ; /* End of class */

#endif /* _PARTICLE_FILTER_BASE_H_ */