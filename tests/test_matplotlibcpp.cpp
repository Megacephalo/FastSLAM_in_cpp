#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "draw.h"
#if 0
TEST(matplotlib_test, build_basic_frame_test) {
	Draw drawer ;
	drawer.draw_basic_frame() ;
	drawer.plot_point(1, 2) ;
	drawer.Show() ;
}
#endif
TEST(matplotlib_test, plot_line_test) {
	// plt::plot( {1, 3} ) ;

	std::vector<double> X, Y ;

	// Drw a line from (1, 1) to (5, 1)
	X = {1, 5, } ;
	Y = {1, 1} ;
	plt::plot(X, Y) ;
	plt::show() ;
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv) ;
    return RUN_ALL_TESTS() ;
}