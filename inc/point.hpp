#pragma once

#include "tools.hpp"
#include <cmath>
#include <iostream>

namespace Geometry {
    class Vector;

    class Point {
        private:
            double x = NAN, y = NAN, z = NAN;

        public:
            Point(){};

            Point(double coord_x, double coord_y, double coord_z) {
                x = coord_x;
                y = coord_y;
                z = coord_z;
            }

            double get_x() const {
                return x;
            }

            double get_y() const {
                return y;
            }

            double get_z() const {
                return z;
            }

            bool is_equal(const Point& point) const {
                return (is_equal_doubles(x, point.x) &&
                is_equal_doubles(y, point.y) && is_equal_doubles(z, point.z) ||
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
}