#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

#include <cmath>  /* M_PI */
#include <random>  /* NOTE: Available only since C++11. std::normal_distribution */
#include <memory>
#include <functional>
#include <numeric>


enum Random_machine_type {
	MERSENNE_TWISTER,
	KNUTH_B,
	DEFAULT
} ;


class Math_utils {
  public:
  	float normalize_angle(float phi) ; //<! Normalize phi to be between -pi and pi
  	float normrnd( const float& mu, const float& sigma
  				 , const Random_machine_type& rd_type = Random_machine_type::MERSENNE_TWISTER) ;
  	float unifrnd( const float& lower_bound, const float& upper_bound
  				 , const Random_machine_type& rd_type = Random_machine_type::MERSENNE_TWISTER) ;
    template<typename T>
    std::vector<T> cumsum(const std::vector<T>& in_vector) ;
  private:
  	std::random_device rd_ ;
} ; /* End of class */


template<typename T>
std::vector<T> Math_utils::cumsum(const std::vector<T>& in_vector) {
  std::vector<T> results ;
  results.resize( in_vector.size() ) ;

  std::partial_sum(in_vector.begin(), in_vector.end(), results.begin()) ;

  return results ;
} /* End of cumsum */

#endif /* _MATH_UTILS_H_ */