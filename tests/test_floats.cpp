#include "octree.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <list>
#include <set>
#include <vector>

const int OPEN_ERROR = -1;

std::set<size_t> get_answer(int test_number) {
    std::set<size_t> answers;

    std::fstream answer_file("../../tests/tests/answer" +
                             std::to_string(test_number) + ".txt");

    if (answer_file.fail()) {
        throw OPEN_ERROR;
    }

    size_t buf;

    while (answer_file >> buf) {
        answers.insert(buf);
    }

    return answers;
}

std::set<size_t> test(int test_number) {
    std::fstream test_file("../../tests/tests/test" +
                           std::to_string(test_number) + ".txt");

    if (test_file.fail()) {
        throw OPEN_ERROR;
    }

    std::cin.rdbuf(test_file.rdbuf());

    size_t triangles_number;
    std::cin >> triangles_number;
    std::list<std::pair<Geometry::Triangle<float>, size_t>> triangles;

    float x_min, y_min, z_min, x_max, y_max, z_max;

    for (int i = 0; i < triangles_number; i++) {
        float x, y, z;
        Geometry::Point<float> triangle_points[3];
        for (int j = 0; j < 3; j++) {
            std::cin >> x >> y >> z;
            triangle_points[j] = Geometry::Point<float>(x, y, z);
            if (i == 0) {
                x_min = x;
                y_min = y;
                z_min = z;
                x_max = x;
                y_max = y;
                z_max = z;
            }
            x_min = x < x_min ? x : x_min;
            y_min = y < y_min ? y : y_min;
            z_min = z < z_min ? z : z_min;
            x_max = x > x_max ? x : x_max;
            y_max = y > y_max ? y : y_max;
            z_max = z > z_max ? z : z_max;
        }

        triangles.emplace_back(Geometry::Triangle<float>(triangle_points[0],
                                                         triangle_points[1],
                                                         triangle_points[2]),
                               i);
    }

    Octree::Octree tree =
        Octree::Octree(triangles, {x_min, y_min, z_min, x_max, y_max, z_max});

    std::set<size_t> res = tree.get_intersections();

    return res;
}

TEST(tests, test1) { ASSERT_TRUE(test(1) == get_answer(1)); }

TEST(tests, test2) { ASSERT_TRUE(test(2) == get_answer(2)); }

TEST(tests, test3) { ASSERT_TRUE(test(3) == get_answer(3)); }

TEST(tests, test4) { ASSERT_TRUE(test(4) == get_answer(4)); }

TEST(tests, test5) { ASSERT_TRUE(test(5) == get_answer(5)); }

TEST(tests, test6) { ASSERT_TRUE(test(6) == get_answer(6)); }

TEST(tests, test7) { ASSERT_TRUE(test(7) == get_answer(7)); }

TEST(tests, test8) { ASSERT_TRUE(test(8) == get_answer(8)); }

TEST(tests, test9) { ASSERT_TRUE(test(9) == get_answer(9)); }

TEST(tests, test10) { ASSERT_TRUE(test(10) == get_answer(10)); }

TEST(tests, test11) { ASSERT_TRUE(test(11) == get_answer(11)); }

TEST(tests, test12) { ASSERT_TRUE(test(12) == get_answer(12)); }

TEST(tests, test13) { ASSERT_TRUE(test(13) == get_answer(13)); }

TEST(tests, test14) { ASSERT_TRUE(test(14) == get_answer(14)); }

TEST(tests, test15) { ASSERT_TRUE(test(15) == get_answer(15)); }

TEST(tests, test16) { ASSERT_TRUE(test(16) == get_answer(16)); }

int main(int argc, char* argv[]) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}