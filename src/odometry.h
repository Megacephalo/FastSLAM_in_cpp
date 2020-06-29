#ifndef _ODOMETRY_H_
#define _ODOMETRY_H_

struct Odometry {
  	Odometry()
  	: timestamp(0)
  	, r1(0.)
  	, t(0.)
  	, r2(0.)
  	{} /* End of default constructor */

    Odometry(const long long& timestamp, const float& r1, const float& t, const float& r2){
      this->timestamp = timestamp ;
      this->r1 = r1 ;
      this->t = t ;
      this->r2 = r2 ;
    } /* End of copy constructor 1 */

    Odometry(const Odometry& new_odom) {
      timestamp = new_odom.timestamp ;
      r1 = new_odom.r1 ;
      t = new_odom.t ;
      r2 = new_odom.r2 ;
    } /* End of copy constructor 2 */

    Odometry& operator = (const Odometry& new_odom) {
      timestamp = new_odom.timestamp ;
      r1 = new_odom.r1 ;
      t = new_odom.t ;
      r2 = new_odom.r2 ;

      return *this ;
    } /* End of assignment operator overloading */

	long long timestamp ;
	float r1 ;
	float t ;
	float r2 ;
} ; /* End of class */

#endif /* _ODOMETRY_H_ */