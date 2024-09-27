#include <iostream>
#include <cmath>
#include <algorithm>

const float EPSILON = 1e-10;

bool is_equal_floats(const float a, const float b) {
    return (std::fabs(a - b)/ (std::max(std::fabs(a) + EPSILON, std::fabs(b) + EPSILON)) < EPSILON);
}

int main() {
    std::cout << (std::min(0, 1) < 0.75 < std::max(0, 1)) << std::endl;
}