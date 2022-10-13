cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( DisplayImage src/DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

add_executable( main src/main.cpp )
target_link_libraries( main ${OpenCV_LIBS} )