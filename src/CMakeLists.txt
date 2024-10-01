cmake_minimum_required(VERSION 3.11)
project(src)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)

target_link_libraries(main geometry)
