cmake_minimum_required(VERSION 3.1)
project(FastSLAM)
ADD_DEFINITIONS(-std=c++11) # C++ 11 is required
set (CMAKE_CXX_STANDARD 11)

# set the compilation mode to RelWithDebInfo (optimized code with debug symbols
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(src)
include_directories(src/tools)
include_directories(src/drawing_utils)

# Import Eigen libraries
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
set(EIGEN_LIBS Eigen3::Eigen)

# Import Python.h
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
message(STATUS "Python version: ${PYTHONLIBS_VERSION_STRING}")
# Message out python and numpy path
message(STATUS "PYTHON_INCLUDE_DIR: ${PYTHON_INCLUDE_DIR}")
add_definitions(-DMATPLOTLIBCPP_PYTHON_HEADER=Python.h)
include_directories(${PYTHON_INCLUDE_DIR})

# CUSTOM LIBRARIRIES
# ~~~~~~~~~~~~~~~~~~
add_library(support_utils
	src/tools/math_utils.cpp
	src/tools/document_processor.cpp
)

add_library(PF_SLAM
	src/sensor_data_importer.cpp
	src/map_importer.cpp
	src/particle_filter_base.cpp
	src/pf_slam.cpp
	src/fast_slam_1.cpp
	src/low_variance_sampling.cpp
	src/measurement_model.cpp
	
)
target_link_libraries(PF_SLAM
	${EIGEN_LIBS}
	support_utils
)

add_library(Drawer
	src/drawing_utils/matplotlibcpp.cpp
	src/drawing_utils/chisquare.cpp
	src/drawing_utils/draw.cpp
)
target_link_libraries(Drawer
	${EIGEN_LIBS}
	${PYTHON_LIBRARIES}

	PF_SLAM
)


# CUSTOM EXEVUTABLES
# ~~~~~~~~~~~~~~~~~~
add_executable( ${PROJECT_NAME}_node
	src/main.cpp
)
target_link_libraries( ${PROJECT_NAME}_node
	PF_SLAM
	Drawer
)

# UNIT TESTS
# ~~~~~~~~~~
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(tests)

add_executable(test_math_utils
	tests/test_math_utils.cpp
)
target_link_libraries(test_math_utils
	${GTEST_LIBRARIES}
	pthread # Required

	support_utils
)

add_executable(test_sensor_data_importer
	tests/test_sensor_data_importer.cpp
)
target_link_libraries(test_sensor_data_importer
	${GTEST_LIBRARIES}
	pthread # Required

	PF_SLAM
)

add_executable(test_matplotlib
	tests/test_matplotlibcpp.cpp
)
target_link_libraries(test_matplotlib
	${GTEST_LIBRARIES}
	pthread # Required

	Drawer
)