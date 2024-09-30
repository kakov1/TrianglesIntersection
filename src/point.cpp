#include "tools.hpp"
#include <iostream>
#include <cmath>

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