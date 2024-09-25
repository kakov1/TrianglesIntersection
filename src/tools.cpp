#include "tools.hpp"
#include "vector.hpp"

bool is_equal_floats(const float a, const float b) {
    return fabs(a - b) < EPSILON;
}

float det_two(const float a11, const float a12, const float a21, const float a22) {
    return a11 * a22 - a21 * a12;
}

bool are_points_collinear(const Point& point1, const Point& point2, const Point& point3) {
    Vector side1(point1, point2);
    Vector side2(point2, point3);
    
    return (!side1.is_collinear(side2));
}

char sign(float number) {
    return number<0?'-':'+';
}