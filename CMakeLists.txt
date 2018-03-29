cmake_minimum_required(VERSION 2.8)

project(graduationproject)

set(raspicam_DIR "/usr/local/lib/cmake")

find_package(OpenCV REQUIRED)
find_package(PCL 1.2 REQUIRED)
find_package(raspicam REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(main Hardware.cpp SurfaceReconstruct.cpp ImageProcessing.cpp DataProcessing.cpp main.cpp)
target_link_libraries(main ${OpenCV_LIBS} ${PCL_LIBRARIES} wiringPi ${raspicam_CV_LIBS})