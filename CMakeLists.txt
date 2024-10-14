cmake_minimum_required(VERSION 3.11)
project("Triangles_intersection")

find_package(GTest REQUIRED)

file(GLOB projectSRC
    "*/*.cpp"
    "*/*.hpp"
    "*.cpp"
    "*.hpp"
)

set(CMAKE_CXX_STANDARD 20)

add_library(geometry ./inc/line.hpp ./inc/octree.hpp ./inc/plane.hpp ./inc/point.hpp
                     ./inc/segment.hpp ./inc/triangle.hpp ./inc/vector.hpp)

target_include_directories(geometry PUBLIC ./inc)

set_target_properties(geometry PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(./src)
add_subdirectory(./tests)
