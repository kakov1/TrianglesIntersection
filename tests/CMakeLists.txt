cmake_minimum_required(VERSION 3.11)
project(tests)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(test test.cpp)

target_link_libraries(test geometry)
target_link_libraries(test gtest gmock pthread)