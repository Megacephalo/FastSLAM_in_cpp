#ifndef _MEASUREMENT_MODEL_H_
#define _MEASUREMENT_MODEL_H_

#include <vector>
#include <Eigen/Dense>
#include <cmath>

#include "common_typedefs.h"
#include "particle.h"
#include "observation.h"
#include "math_utils.h"

class Measurement_model {
  public:
  	Measurement_model(const Particle& particle, const Observation_model& obs) ;
  	void calc_exp_z(const Particle& particle, const Observation_model& obs) ;

  	Eigen::Vector2d h() const ;
  	Eigen::Matrix2d H() const ;

  	Measurement_model& operator = ( const Measurement_model& new_obs ) ;
  private:
  	Math_utils math_ ;

  	Eigen::Vector2d h_ ;
  	Eigen::Matrix2d H_ ;
} ; /* End of class */

#endif /* _MEASUREMENT_MODEL_H_ */