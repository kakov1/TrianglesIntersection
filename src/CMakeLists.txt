cmake_minimum_required(VERSION 3.11)
project("Triangles_intersection")

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp point.cpp plane.cpp point.cpp tools.cpp vector.cpp segment.cpp line.cpp triangle.cpp)
