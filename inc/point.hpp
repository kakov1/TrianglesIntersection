#pragma once

#include <cmath>

class Point {
    private:
        double x = NAN, y = NAN, z = NAN;
    public:
        Point() {};
        Point(double coord_x, double coord_y, double coord_z);

        double get_x() const;
        double get_y() const;
        double get_z() const;

        void print() const;
        bool is_equal(const Point& point) const;
        bool is_valid() const;
        bool is_nan() const; 
        bool are_points_collinear(const Point& point1, const Point& point2) const;
};