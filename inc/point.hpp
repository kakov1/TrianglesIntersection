#pragma once

#include "tools.hpp"
#include <cmath>
#include <iostream>

namespace Geometry {
template <typename FloatType> class Point {
private:
  FloatType x = NAN, y = NAN, z = NAN;

public:
  Point() = default;

  Point(FloatType coord_x, FloatType coord_y, FloatType coord_z) {
    x = coord_x;
    y = coord_y;
    z = coord_z;
  }

  const FloatType &get_x() const { return x; }

  const FloatType &get_y() const { return y; }

  const FloatType &get_z() const { return z; }

  bool is_equal(const Point &point) const {
    return (is_equal_floats(x, point.x) && is_equal_floats(y, point.y) &&
                is_equal_floats(z, point.z) ||
            (is_nan() && point.is_nan()));
  }

  bool is_nan() const {
    return (std::isnan(x) && std::isnan(y) && std::isnan(z));
  }

  void print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
  }

  bool is_valid() const {
    return (!std::isnan(x) && !std::isnan(y) && !std::isnan(z));
  }
};
} // namespace Geometry