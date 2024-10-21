add_executable(test_doubles test_doubles.cpp)
add_executable(test_floats test_floats.cpp)

target_link_libraries(test_doubles geometry)
target_link_libraries(test_doubles gtest gmock pthread)
target_link_libraries(test_floats geometry)
target_link_libraries(test_floats gtest gmock pthread)