#include <iostream>
#include <string>

#include "pf_slam.h"

int main(int argc, char** argv) {
	std::cout << "Launching PF SLAM.\n" ;

	// std::string odom_data_file = argv[1] ;
	std::string odom_data_file ( "../data/sensor_data.dat" ) ;
	std::string map_data_file("../data/world.dat") ;

	PF_SLAM pf_SLAM(odom_data_file, map_data_file, true, true) ;

	pf_SLAM.run() ;

	std::cout << "Done!\n" ;

	return 0 ;
}