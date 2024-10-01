#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "tools.hpp"

class Line {
    private:
        Point start_point = NAN_POINT;
        Vector direction_vector = NAN_VECTOR;
    public:
        Line() {};
        Line(const Point& point1, const Point& point2);
        Line(const Point& point, const Vector& vector);

        Point get_start_point() const;
        Vector get_direction_vector() const;

        Point lines_intersection(const Line& line) const;
        bool is_equal(const Line& line) const;
        bool is_point_belong(const Point& point) const;
        bool is_parallel(const Line& line) const;
        void print() const;
};