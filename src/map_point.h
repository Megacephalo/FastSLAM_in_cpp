#ifndef _MAP_POINT_H_
#define _MAP_POINT_H_

#include <ostream>
#include <vector>

struct MapPoint {
	MapPoint()
	: id(0)
	, x(0)
	, y(0)
	{} /* End of construcot */

	long long id ;
	float x ;
	float y ;
} ; /* End of struct */



#endif /* _MAP_POINT_H_ */