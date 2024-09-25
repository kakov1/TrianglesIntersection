#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "tools.hpp"

class Line {
    public:
        Point start_point = NAN_POINT;
        Vector direction_vector = NAN_VECTOR;

        Line() {};
        Line(const Point& point1, const Point& point2) {
            start_point = point1;
            direction_vector = {point1, point2};
        }
        Line(const Point& point, const Vector& vector) {
            start_point = point;
            direction_vector = vector;
        }

        Point lines_intersection(const Line& line) const;
        bool is_equal(const Line& line) const;
        bool is_point_belong(const Point& point) const;
        bool is_parallel(const Line& line) const;
        //bool is_valid() const;
        //bool is_on_same_line(const Segment& segment) const;
        //float distance_between_lines(const Segment& segment) const;
};