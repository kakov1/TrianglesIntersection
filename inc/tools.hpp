#pragma once

#include <vector>
#include <limits>
#include <cmath>
#include <utility>
#include <algorithm>

namespace Geometry {
    const double EPSILON                              = 1e-8;
    const std::pair<double, double> NAN_SOLUTION      = { NAN, NAN };
    const std::pair<double, double> INFINITY_SOLUTION = { INFINITY, INFINITY };

    bool is_equal_doubles(const double a, const double b) {
        return (std::fabs(a - b) < EPSILON);
    }

    bool is_double_in_segment(double number, double a, double b) {
        return (std::min(a, b) < number) && (number < std::max(a, b)) ||
        is_equal_doubles(number, a) || is_equal_doubles(number, b);
    }

    double det_two(const double a11, const double a12, const double a21, const double a22) {
        return a11 * a22 - a21 * a12;
    }

    char sign(double number) {
        return number < 0 ? '-' : '+';
    }

    std::pair<double, double> solve_system_2eq_2var(const std::vector<double>& row1,
    const std::vector<double>& row2) {
        double main_det = det_two(row1[0], row1[1], row2[0], row2[1]);
        double x_det    = det_two(row1[2], row1[1], row2[2], row2[1]);
        double y_det    = det_two(row1[0], row1[2], row2[0], row2[2]);

        if (is_equal_doubles(main_det, 0)) {
            if (is_equal_doubles(x_det, 0) && is_equal_doubles(y_det, 0)) {
                return { INFINITY, INFINITY };
            }
            else {
                return { NAN, NAN };
            }
        }
        else {
            return { x_det / main_det, y_det / main_det };
        }
    }

    bool is_nan_solution(std::pair<double, double> solution) {
        return std::isnan(solution.first) && std::isnan(solution.second);
    }

    bool is_inf_solution(std::pair<double, double> solution) {
        return std::isinf(solution.first) && std::isinf(solution.second);
    }

    bool is_equal_solutions(std::pair<double, double> solution1,
    std::pair<double, double> solution2) {
        return is_equal_doubles(solution1.first, solution2.first) &&
        is_equal_doubles(solution1.second, solution2.second);
    }

    std::pair<double, double> solve_system_3eq_2var(const std::vector<double>& row1,
    const std::vector<double>& row2,
    const std::vector<double>& row3) {
        std::pair<double, double> solution12 = solve_system_2eq_2var(row1, row2);
        std::pair<double, double> solution23 = solve_system_2eq_2var(row2, row3);
        std::pair<double, double> solution13 = solve_system_2eq_2var(row1, row3);

        if (is_inf_solution(solution12) && is_inf_solution(solution23) &&
        is_inf_solution(solution13))
            return INFINITY_SOLUTION;

        if (is_inf_solution(solution12) && is_inf_solution(solution23))
            return solution13;

        if (is_inf_solution(solution12) && is_inf_solution(solution13))
            return solution23;

        if (is_inf_solution(solution23) && is_inf_solution(solution13))
            return solution12;

        if (is_inf_solution(solution12))
            return solution23;

        if (is_inf_solution(solution23))
            return solution13;

        if (is_inf_solution(solution13))
            return solution12;

        if (is_equal_solutions(solution12, solution13) &&
        is_equal_solutions(solution12, solution23)) {
            return solution12;
        }
        else {
            return NAN_SOLUTION;
        }
    }
}