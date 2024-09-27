#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "segment.hpp"
#include <limits>
#include <cmath>
#include <utility>

const float EPSILON = 0.0001;
const Point NAN_POINT = {NAN, NAN, NAN};
const Point INFINITY_POINT = {INFINITY, INFINITY, INFINITY};
const Vector NAN_VECTOR = {NAN, NAN, NAN};
const Segment NAN_SEGMENT = {NAN_POINT, NAN_POINT};
const std::pair<float, float> NAN_SOLUTION = {NAN, NAN};
const std::pair<float, float> INFINITY_SOLUTION = {INFINITY, INFINITY};

bool is_equal_floats(float a, float b);
bool is_float_in_segment(float number, float a, float b);
float det_two(float a11, float a12, float a21, float a22);
bool are_points_collinear(const Point& point1, const Point& point2, const Point& point3);
char sign(float number);
std::pair<float, float> solve_system_3eq_2var(const Vector& col1, const Vector& col2, const Vector& col3);
std::pair<float, float> solve_system_2eq_2var(const Vector& row1, const Vector& row2);
bool is_nan_solution(std::pair<float, float> solution);
bool is_inf_solution(std::pair<float, float> solution);