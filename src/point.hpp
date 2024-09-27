#pragma once

#include <cmath>

class Point {
    public:
        double x = NAN, y = NAN, z = NAN;
        
        Point() {};
        Point(double coord_x, double coord_y, double coord_z) {
            x = coord_x;
            y = coord_y;
            z = coord_z;
        }
        void print() const;
        bool is_equal(const Point& point) const;
        bool is_valid() const;
        bool is_nan() const; 
};