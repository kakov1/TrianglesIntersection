#include "tools.hpp"
#include "point.hpp"
#include "vector.hpp"
#include <algorithm>
#include <utility>
#include <cmath>

bool Geometry::is_equal_doubles(const double a, const double b) {
    return (std::fabs(a - b) < EPSILON);
}

bool Geometry::is_double_in_segment(double number, double a, double b) {
    return (std::min(a, b) < number) && (number < std::max(a, b)) ||
            is_equal_doubles(number, a) || is_equal_doubles(number, b);
}

double Geometry::det_two(const double a11, const double a12, const double a21, const double a22) {
    return a11 * a22 - a21 * a12;
}

char Geometry::sign(double number) {
    return number<0?'-':'+';
}

std::pair<double, double> Geometry::solve_system_2eq_2var(const Vector& row1,
                                                          const Vector& row2) {
    double main_det = det_two(row1.get_x(), row1.get_y(),
                              row2.get_x(), row2.get_y());
    double x_det = det_two(row1.get_z(), row1.get_y(),
                           row2.get_z(), row2.get_y());
    double y_det = det_two(row1.get_x(), row1.get_z(),
                           row2.get_x(), row2.get_z());
    
    if (is_equal_doubles(main_det, 0)) {
        if (is_equal_doubles(x_det, 0) && is_equal_doubles(y_det, 0)) {
            return {INFINITY, INFINITY};
        }
        else {
            return {NAN, NAN};
        }
    }
    else {
        return {x_det/main_det, y_det/main_det};
    }
}

bool Geometry::is_nan_solution(std::pair<double, double> solution) {
    return std::isnan(solution.first) && std::isnan(solution.second);
}

bool Geometry::is_inf_solution(std::pair<double, double> solution) {
    return std::isinf(solution.first) && std::isinf(solution.second);
}

bool Geometry::is_equal_solutions(std::pair<double, double> solution1,
                                  std::pair<double, double> solution2) {
    return is_equal_doubles(solution1.first, solution2.first) &&
           is_equal_doubles(solution1.second, solution2.second);
}

std::pair<double, double> Geometry::solve_system_3eq_2var(const Vector& row1,
                                                          const Vector& row2,
                                                          const Vector& row3) {
    std::pair<double, double> solution12 = solve_system_2eq_2var(row1, row2);
    std::pair<double, double> solution23 = solve_system_2eq_2var(row2, row3);
    std::pair<double, double> solution13 = solve_system_2eq_2var(row1, row3);

    if (is_inf_solution(solution12) &&
        is_inf_solution(solution23) &&
        is_inf_solution(solution13)) return INFINITY_SOLUTION;

    if (is_inf_solution(solution12) &&
        is_inf_solution(solution23)) return solution13;

    if (is_inf_solution(solution12) &&
        is_inf_solution(solution13)) return solution23;

    if (is_inf_solution(solution23) &&
        is_inf_solution(solution13)) return solution12;

    if (is_inf_solution(solution12)) return solution23;

    if (is_inf_solution(solution23)) return solution13;

    if (is_inf_solution(solution13)) return solution12;
    
    if (is_equal_solutions(solution12, solution13) &&
        is_equal_solutions(solution12, solution23)) {
        return solution12;
    }
    else {
        return NAN_SOLUTION;
    }
}