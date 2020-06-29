#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <Eigen/Dense>
#include <list>
#include <vector>
#include "landmark.h"

struct Particle {
	Particle()
	: weight(0.)
	, state( Eigen::Vector3d::Zero(3) )
	{
		landmarks.clear() ;
		history.clear() ;
	} /* End of default constructor */

	Particle( const Particle& part ) {
		state = part.state ;
		weight = part.weight ;
		history = part.history ;
		landmarks = part.landmarks ;
	} /* End of copy constructor overloading 1 */

	Particle( const Eigen::Vector3d& new_state
			, const std::vector<Landmark>& landmarks
			, const float& new_weight
			, const std::list<Eigen::VectorXd>& new_history) {
		this->state = new_state ;
		this->landmarks = landmarks ;
		this->weight = new_weight ;
		this->history = new_history ;
	} /* End of copy constructor overloading 2 */

	Particle& operator = (const Particle& part) {
		state = part.state ;
		landmarks = part.landmarks ;
		weight = part.weight ;
		history = part.history ;

		return *this ;
	} /* End of assignment operator overloading */

	Eigen::Vector3d state ; // (x, y ,theta)
	std::vector<Landmark> landmarks ; // The estimated pose and certainty of the perceived landmarks
	float weight ;
	std::list<Eigen::VectorXd> history ; // the path which contains all the past poses

} ; /* End of class */

#endif /* _PARTICLE_H_ */