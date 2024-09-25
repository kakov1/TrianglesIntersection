#pragma once

#include "point.hpp"
#include "vector.hpp"
#include <limits>
#include <cmath>

const float EPSILON = std::numeric_limits<float>::epsilon();
const Point NAN_POINT = {NAN, NAN, NAN};
const Point INFINITY_POINT = {INFINITY, INFINITY, INFINITY};
const Vector NAN_VECTOR = {NAN, NAN, NAN};

bool is_equal_floats(float a, float b);
float det_two(float a11, float a12, float a21, float a22);
bool are_points_collinear(const Point& point1, const Point& point2, const Point& point3);
char sign(float number);