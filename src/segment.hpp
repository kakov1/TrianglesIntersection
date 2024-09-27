#pragma once

#include "point.hpp"
#include "vector.hpp"


class Segment {
    public:
        Point start_point;
        Point end_point;
        Vector direction_vector;

        Segment() {};
        Segment(const Point& point1, const Point& point2) {
            start_point = point1;
            end_point = point2;
            direction_vector = {point2.x - point1.x,
                                point2.y - point1.y,
                                point2.z - point1.z};
            direction_vector.normalize();
        }

        bool is_point_belong(const Point& point) const;
        bool is_valid() const;
        bool is_nan() const;
        void print() const;
        bool is_on_same_line(const Segment& segment) const;
        double distance_between_lines(const Segment& segment) const;
        Point segments_intersection(const Segment& segment) const;
};