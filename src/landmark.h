#ifndef _LANDMARK_H_
#define _LANDMARK_H_

#include <Eigen/Dense>

struct Landmark {
  public:
  	Landmark()
  	: observed(false)
  	, mu( Eigen::Vector2d::Zero(2) )
  	, sigma( Eigen::Matrix2d::Zero(2, 2))
  	{} /* End of default constructor */

  	Landmark(const Landmark& new_landmark) {
  		observed = new_landmark.observed ;
  		mu = new_landmark.mu ;
  		sigma = new_landmark.sigma ;
  	} /* End of copy constructor 1 */

  	Landmark(const bool& observed, const Eigen::Vector2d& mu, const Eigen::Matrix2d& sigma) {
  		this->observed = observed ;
  		this->mu = mu ;
  		this->sigma = sigma ;
  	} /* End of copy constructor 2 */

  	Landmark& operator = (const Landmark& new_landmark) {
  		observed = new_landmark.observed ;
  		mu = new_landmark.mu ;
  		sigma = new_landmark.sigma ;

  		return *this ;
  	} /* End of assignment operator overloading */

  	bool observed ;
  	Eigen::Vector2d mu ;
  	Eigen::Matrix2d sigma ;
} ; /* End of struct */

#endif /* _LANDMARK_H_ */