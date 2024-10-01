cmake_minimum_required(VERSION 3.11)
project("Triangles_intersection")

set(CMAKE_CXX_STANDARD 20)

add_library(geometry ./src/line.cpp ./src/plane.cpp ./src/point.cpp ./src/segment.cpp
                     ./src/tools.cpp ./src/triangle.cpp ./src/vector.cpp)

target_include_directories(geometry PUBLIC ./inc)

add_subdirectory(./src)
add_subdirectory(./tests)
