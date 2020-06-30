#ifndef _COMMON_TYPEDEFS_H_
#define _COMMON_TYPEDEFS_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <memory>

#include "odometry.h"
#include "particle.h"
#include "map_point.h"
#include "landmark.h"
#include "observation.h"
#include "sensor_record.h"

typedef std::vector<Odometry> odom_data ;
typedef std::vector<MapPoint> mapPointSet ;
typedef std::vector<Particle> ParticleSet ;
typedef std::shared_ptr<ParticleSet> ParticleSetPtr ; // think of it as equivalent to ParticleSet
typedef std::vector<Landmark> LandmarkSet ;
typedef std::vector<Observation_model> Observations ;
typedef std::vector<Sensor_record> Records ;


/* Operators overloading to ease in debugging */

// Odometry
inline std::ostream& operator << (std::ostream& os, const Odometry& odom) {
	os 	<< std::left << std::setw(25) << "Odometry timestamp: " << std::left << std::setw(5) << odom.timestamp 
		<< std::setw(10) << "r1: " << std::left << std::setw(15) << odom.r1
		<< std::setw(10) << "t: " << std::left << std::setw(15) << odom.t
		<< std::setw(10) << "r2: " << std::left << std::setw(15) << odom.r2 ;
	return os ;
}


// odom_data
inline std::ostream& operator << (std::ostream& os, const odom_data& odoms) {
	os << "------------------------------------\n" ;
	odom_data::const_iterator it ;
	for (it = odoms.begin() ; it != odoms.end() ; it++) {
		os << *it ;
	}
	os << "------------------------------------\n" ;
	return os ;
}

// Particle
inline std::ostream& operator << (std::ostream& os, const Particle& particle) {
	int history_size = particle.history.size() ;
	int numLandmarks = (int)particle.landmarks.size() ;
	os << "Pose(x: " << std::setw(13) << particle.state(0) << ", y: " << std::setw(13) << particle.state(1) << ", theta: " << std::setw(13) << particle.state(2) << std::setw(5) << ")"
	   << std::left << std::setw(10) << "weight: " << std::setw(5) << particle.weight
	   << "history: " << std::setw(3) << history_size << ( (history_size == 1) ? " past pose" : " past poses")
	   << " and contains: " << std::setw(5) << numLandmarks << ( (numLandmarks == 1 || numLandmarks == 0) ? "landmark" : "landmarks" ) ;
	return os ;
}

// ParticleSet
inline std::ostream& operator << (std::ostream& os, const ParticleSet& particles) {
	std::vector<Particle>::const_iterator it ;
	for (it = particles.begin() ; it != particles.end() ; ++it) {
		os << *it << std::endl ;
	}
	return os ;
}

inline std::ostream& operator << (std::ostream& os, const ParticleSetPtr& particlesPtr) {
	os << *particlesPtr ;
	return os ;
}

// MapPoint
inline std::ostream& operator << (std::ostream& out, const MapPoint& mapPoint) {
	out << std::to_string(mapPoint.id) << ": (" + std::to_string(mapPoint.x) << ", " << std::to_string(mapPoint.y) << ")" ;
	return out ;
} /* End of operator << overloading for MapPoint */

// mapPointSet
inline std::ostream& operator << (std::ostream& os, const mapPointSet& landmarks) {
	std::vector<MapPoint>::const_iterator it ;
	for (it = landmarks.begin() ; it != landmarks.end() ; it++) {
		os << *it ;
	}

	return os ;
} /* End of operator << overloading for vector of MapPoints */

// Landmark
inline std::ostream& operator << (std::ostream& os, const Landmark& landm) {
	os 	<< "Landmark mu = [ " << landm.mu.transpose() << " ]^T" << std::endl 
   		<< "sigma = [ " << landm.sigma << " ]" << std::endl 
   		<< (landm.observed ? "has been observed" : "has NOT been seen yet") ;
   	return os ;
}

// LandmarkSet
inline std::ostream& operator << (std::ostream& os, const LandmarkSet& landmarks) {
	for( auto landm : landmarks ) {
		os << landm ;
	}
	return os ;
}

// Observation_model
inline std::ostream& operator << (std::ostream& os, const Observation_model& observation) {
	os 	<< std::left << std::setw(25) << "Observation timestamp: " << std::left << std::setw(5) << observation.timestamp
		<< std::setw(10) << "ID: " << std::left << std::setw(15) << observation.id 
		<< std::setw(10) << "range: " << std::left << std::setw(15) << observation.range
		<< std::setw(10) << "bearing: " << std::left << std::setw(15) << observation.bearing ;
	return os ;
}

// Observations
inline std::ostream& operator << (std::ostream& os, const Observations& observations) {
	for (auto obs : observations) {
		os << obs << std::endl ;
	}
	return os ;
}

// Sensor_record
inline std::ostream& operator << (std::ostream& os, const Sensor_record& record) {
	os 	<< "\nrecord: " << std::endl 
		<< std::left << std::setw(15) << "Odometry: " << std::endl 
		<< std::left << record.odom << std::endl
		<< std::left << std::setw(15) << "Observations: " << std::endl
		<< std::left << record.observations ;
	return os ;
} 

// Records
inline std::ostream& operator << (std::ostream& os, const Records& records) {
	for (auto record : records) {
		os << record << std::endl ;
	}
	return os ;
}

#endif /* _COMMON_TYPEDEFS_H_ */