#include "tools.hpp"
#include <iostream>

bool Point::is_equal(const Point& point) const{
    return is_equal_floats(x, point.x) &&
           is_equal_floats(y, point.y) &&
           is_equal_floats(z, point.z);
}

void Point::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

bool Point::is_valid() const {
    return (!std::isnan(x) && !std::isnan(y) && !std::isnan(z));
}