#include "tools.hpp"
#include <iostream>
#include <cmath>

double Point::get_x() const { return x; }
double Point::get_y() const { return y; }
double Point::get_z() const { return z; }

Point::Point(double coord_x, double coord_y, double coord_z) {
    x = coord_x;
    y = coord_y;
    z = coord_z;
}

bool Point::is_equal(const Point& point) const{
    return (is_equal_doubles(x, point.x) &&
            is_equal_doubles(y, point.y) &&
            is_equal_doubles(z, point.z) ||
            (is_nan() && point.is_nan()));
}

bool Point::is_nan() const {
    return (std::isnan(x) && std::isnan(y) && std::isnan(z));
}

void Point::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

bool Point::is_valid() const {
    return (!std::isnan(x) && !std::isnan(y) && !std::isnan(z));
}

bool Point::are_points_collinear(const Point& point1, const Point& point2) const {
    Vector side1(*this, point1);
    Vector side2(point1, point2);
    
    return (side1.is_collinear(side2));
}