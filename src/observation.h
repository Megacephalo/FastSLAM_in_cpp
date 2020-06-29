#ifndef _OBSERVATION_H_
#define _OBSERVATION_H_

struct Observation_model {
	Observation_model()
	: timestamp(0)
	, id(0)
	, range(0.)
	, bearing(0.)
	{} /* End of default constructor */

	Observation_model(const Observation_model& new_obs) {
		timestamp = new_obs.timestamp ;
		id = new_obs.id ;
		range = new_obs.range ;
		bearing = new_obs.bearing ;
	} /* End of copy constructor overloading 1 */ 

	Observation_model(const long long& timestamp, const long long& id, const float& range, const float& bearing) {
		this->timestamp = timestamp ;
		this->id = id ;
		this->range = range ;
		this->bearing = bearing ;
	} /* End of copy constructor overloading 2 */

	Observation_model& operator = (const Observation_model& obs) {
		timestamp = obs.timestamp ;
		id = obs.id ;
		range = obs.range ;
		bearing = obs.bearing ;

		return *this ;
	} /* End of assignment operator overloading */

	long long timestamp ;
	long long id ;
	float range ;
	float bearing ;
} ; /* End of struct */

#endif /* _OBSERVATION_H_ */