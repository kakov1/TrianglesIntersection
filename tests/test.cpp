#include "triangle.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>
#include <vector>

const int OPEN_ERROR = -1;

std::vector<size_t> get_answer(int test_number) {
    std::vector<size_t> answers;
    
    std::fstream answer_file("../../tests/tests/answer" + std::to_string(test_number) + ".txt");

    if (answer_file.fail()) {
        throw OPEN_ERROR;
    }

    size_t buf;

    while (answer_file >> buf) {
        answers.push_back(buf);
    }
    
    return answers;


}
std::vector<size_t> test(int test_number) {
    std::vector<size_t> answer;
    std::fstream test_file("../../tests/tests/test" + std::to_string(test_number) + ".txt");

    if (test_file.fail()) {
        throw OPEN_ERROR;
    }

    std::cin.rdbuf(test_file.rdbuf()); 

    size_t triangles_number;

    std::cin >> triangles_number;

    std::vector<Triangle> triangles;

    for (int i = 0; i < triangles_number; i++) {
        double x, y, z;
        std::vector<Point> triangle_points;
        for (int j = 0; j < 3; j++) {
            std::cin >> x >> y >> z;
            triangle_points.push_back(Point(x, y, z));
        }
        triangles.emplace_back(triangle_points[0], triangle_points[1], triangle_points[2]);
    }

    for (int i = 0; i < triangles_number; i++) {
        for (int j = 0; j < triangles_number; j++) {
            if (i != j && triangles[i].is_intersect(triangles[j])) {
                answer.push_back(i);
                break;
            }
        }
    }
    return answer;
}

TEST(tests, test1) {
    ASSERT_TRUE(test(1) == get_answer(1));
}

TEST(tests, test2) {
    ASSERT_TRUE(test(2) == get_answer(2));
}

TEST(tests, test3) {
    ASSERT_TRUE(test(3) == get_answer(3));
}

TEST(tests, test4) {
    ASSERT_TRUE(test(4) == get_answer(4));
}

TEST(tests, test5) {
    ASSERT_TRUE(test(5) == get_answer(5));
}

TEST(tests, test6) {
    ASSERT_TRUE(test(6) == get_answer(6));
}

TEST(tests, test7) {
    ASSERT_TRUE(test(7) == get_answer(7));
}

TEST(tests, test8) {
    ASSERT_TRUE(test(8) == get_answer(8));
}

TEST(tests, test9) {
    ASSERT_TRUE(test(9) == get_answer(9));
}

TEST(tests, test10) {
    ASSERT_TRUE(test(10) == get_answer(10));
}

TEST(tests, test11) {
    ASSERT_TRUE(test(11) == get_answer(11));
}

TEST(tests, test12) {
    ASSERT_TRUE(test(12) == get_answer(12));
}

TEST(tests, test13) {
    ASSERT_TRUE(test(13) == get_answer(13));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}