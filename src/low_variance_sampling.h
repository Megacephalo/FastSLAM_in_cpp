#ifndef _LOW_VARIANCE_SAMPLING_H_
#define _LOW_VARIANCE_SAMPLING_H_

#include "common_typedefs.h"
#include "math_utils.h"

class Low_variance_sampling {
  public:
  	void sample(ParticleSet& particles, const std::vector<double>& all_weights) ;
  	void sample(ParticleSet& particles, const std::vector<float>& all_weights) ;

  private:
  	Math_utils math_ ;
} ; /* End of class */

#endif /* _LOW_VARIANCE_SAMPLING_H_ */