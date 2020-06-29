#ifndef _SENSOR_RECORD_H_
#define _SENSOR_RECORD_H_

#include <vector>

#include "odometry.h"
#include "observation.h"

struct Sensor_record {
	Sensor_record()
	{
		observations.clear() ;
	} /* End of default constructor */

	void clear() {
		odom = Odometry(0, 0., 0., 0.) ;
		observations.clear() ;
	}

	Odometry odom ;
	std::vector<Observation_model> observations ;
} ; /* End of struct */

#endif /* _SENSOR_RECORD_H_ */