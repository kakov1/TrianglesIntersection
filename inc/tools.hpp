#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "segment.hpp"
#include <limits>
#include <cmath>
#include <utility>

namespace Geometry {
    const double EPSILON = 1e-8;
    const Point NAN_POINT = {NAN, NAN, NAN};
    const Point INFINITY_POINT = {INFINITY, INFINITY, INFINITY};
    const Vector NAN_VECTOR = {NAN, NAN, NAN};
    const Segment NAN_SEGMENT = {NAN_POINT, NAN_POINT};
    const std::pair<double, double> NAN_SOLUTION = {NAN, NAN};
    const std::pair<double, double> INFINITY_SOLUTION = {INFINITY, INFINITY};

    bool is_equal_doubles(double a, double b);
    bool is_double_in_segment(double number, double a, double b);
    double det_two(double a11, double a12, double a21, double a22);
    char sign(double number);
    std::pair<double, double> solve_system_3eq_2var(const Vector& col1, const Vector& col2, const Vector& col3);
    std::pair<double, double> solve_system_2eq_2var(const Vector& row1, const Vector& row2);
    bool is_equal_solutions(std::pair<double, double> solution1, std::pair<double, double> solution2);
    bool is_nan_solution(std::pair<double, double> solution);
    bool is_inf_solution(std::pair<double, double> solution);
}