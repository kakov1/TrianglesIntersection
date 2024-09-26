#pragma once

#include "segment.hpp"
#include "point.hpp"
#include "plane.hpp"

class Triangle {
    public:
        Point a;
        Point b;
        Point c;
        Plane plane;

        Triangle(const Point& point1, const Point& point2, const Point& point3) {
            a = point1;
            b = point2;
            c = point3;
            plane = Plane(a, b, c);
        }

        bool is_valid() const;
        bool is_intersect(const Triangle& triangle) const;
        bool is_intersect_in_same_plane(const Triangle& triangle) const;
        bool is_in_same_half_plane(const Plane& plane) const;
        bool overlap_method(const Triangle& triangle);
        Segment intersection_line_in_same_plane(const Line& line) const;
};