#include "tools.hpp"
#include "vector.hpp"
#include <iostream>

int main() {
    Vector row1 = {1, 1, 3};
    Vector row2 = {2, 2, 6};
    Vector row3 = {3, 5, 6};

    std::pair<double, double> solution = solve_system_3eq_2var(row1, row2, row3);
    std::cout << solution.first << solution.second << std::endl;
}