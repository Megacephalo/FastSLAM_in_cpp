#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "math_utils.h"

TEST(Math_utils_test, cumsum_test) {
	Math_utils math ;

	std::vector<int> v = {1, 2, 3, 4, 5} ;
	std::vector<int> outVect = math.cumsum<int>(v) ;

	for (auto ele : outVect) {
		std::cout << ele << " " ;
	}
	std::cout << std::endl ;


	std::vector<double> v1 = {1.2, 3.1, 4.5} ;
	std::vector<double> outVect1 = math.cumsum(v1) ;
	for (auto ele : outVect1) {
		std::cout << ele << " " ;
	}
	std::cout << std::endl ;

	std::vector<int> v2 = {1} ;
	std::vector<int> outVect2 = math.cumsum(v2) ;
	for (auto ele : outVect2) {
		std::cout << ele << " " ;
	}
	std::cout << std::endl ;	

	std::vector<int> v3 ;
	v3.clear() ;
	std::vector<int> outVect3 = math.cumsum(v3) ;
	for (auto ele : outVect3) {
		std::cout << ele << " " ;
	}
	std::cout << std::endl ;	
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv) ;
    return RUN_ALL_TESTS() ;
}