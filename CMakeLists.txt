cmake_minimum_required(VERSION 3.11)
project("Triangles_intersection")

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_library(geometry INTERFACE)

target_include_directories(geometry INTERFACE ./inc)

add_subdirectory(./src)
add_subdirectory(./tests)
