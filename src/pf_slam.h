#ifndef _PF_SLAM_H_
#define _PF_SLAM_H_

#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream> /* stringstream */

#include "common_typedefs.h"
#include "draw.h"
#include "sensor_data_importer.h"
#include "map_importer.h"
#include "particle_filter_base.h"
#include "fast_slam_1.h"
#include "landmark.h"

enum PF_SLAM_Type {
  FAST_SLAM_1,
  FAST_SLAM_2
} ; /* End of enum */

class PF_SLAM {
  public:
  	PF_SLAM( const std::string& sensor_data_file
           , const std::string& map_data_file
           , const bool& visualize = false
           , const bool& save_frames = false
           , const int& numParticles = 100
           , const PF_SLAM_Type& pfSlam_type = FAST_SLAM_1 ) ;
  	void run() ;

  private:
  	Draw drawer_ ;
  	Sensor_data_importer sensor_import_ ;
    Map_Importer map_import_ ;
  	std::unique_ptr<Particle_filter_base> fastSlam_ ;
    Records all_sensor_records_ ;
    mapPointSet landmarks_ ;
    Eigen::Vector3d noises_ ;
    ParticleSetPtr particles_ ;
    bool visualize_ ;
    bool save_frames_ ;
} ; /* End of class */

#endif /* _PF_SLAM_H_ */