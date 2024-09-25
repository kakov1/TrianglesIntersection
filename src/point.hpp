#pragma once

#include <cmath>

class Point {
    public:
        float x = NAN, y = NAN, z = NAN;
        
        Point() {};
        Point(float coord_x, float coord_y, float coord_z) {
            x = coord_x;
            y = coord_y;
            z = coord_z;
        }
        void print() const;
        bool is_equal(const Point& point) const;
        bool is_valid() const;
};