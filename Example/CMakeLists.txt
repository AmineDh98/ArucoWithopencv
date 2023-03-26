cmake_minimum_required(VERSION 3.1)
project(example)

set (CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

include_directories(${OPENCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${OpenCV_LIBRARY_DIRS})

set(example_src
    src/filtering.cpp
    src/camera_calibration.cpp
    src/detect_marker.cpp
    src/draw_cube.cpp
    src/generate_board.cpp
    src/generate_marker.cpp
    src/pose_estimation.cpp
   )
foreach(source_file ${example_src})
   # Get the file name without extension
   get_filename_component(exec_name ${source_file} NAME_WE)
   # Create an executable with the same name as the source file
   add_executable(${exec_name} ${source_file})
   target_link_libraries(${exec_name} ${OpenCV_LIBRARIES})
   target_compile_options(${exec_name} PRIVATE -O3 -std=c++11)
 endforeach()