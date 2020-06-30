#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "draw.h"

TEST(matplotlib_test, ) {
	Draw drawer ;
	drawer.draw_basic_frame() ;
	drawer.plot_point(1, 2) ;
	drawer.Show() ;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv) ;
    return RUN_ALL_TESTS() ;
}