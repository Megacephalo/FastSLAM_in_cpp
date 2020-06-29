#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "sensor_data_importer.h"
#include "common_typedefs.h"
#include "sensor_record.h"

TEST(sensor_data_importer_test, get_test) {
	Sensor_data_importer importer ;

	std::string fileName( "../tests/two_entries_data.dat" ) ;
	importer.import_from(fileName) ;
	std::cout << importer.get() << std::endl ;

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv) ;
    return RUN_ALL_TESTS() ;
}