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
            if (is_segment() && !is_point()) {
                if (!a.is_equal(b) && !b.is_equal(c) && !a.is_equal(c)) {
                    if (Segment(a, b).is_point_belong(c)) {
                        b = point3;
                        c = point2;
                    }
                    else if (Segment(b, c).is_point_belong(a)) {
                        b = point1;
                        a = point2;
                    }
                }    
            }
            if (is_degenerate()) {
                plane = {NAN_POINT, NAN_POINT, NAN_POINT};
                return;
            }
            plane = Plane(a, b, c);
        }

        bool is_valid() const;
        bool is_point() const;
        bool is_segment() const;
        bool is_equal(const Triangle& triangle) const;
        bool is_point_belong(const Point& point) const;
        bool is_degenerate() const;
        bool is_intersect(const Triangle& triangle) const;
        bool is_intersect_in_same_plane(const Triangle& triangle) const;
        bool is_intersect_segment(const Segment& segment) const;
        bool is_in_same_half_plane(const Plane& plane) const;
        bool overlap_method(const Triangle& triangle);
        Segment intersection_line_in_same_plane(const Line& line) const;
        Point get_vertice(int number) const;
        int get_middle_index(int index1, int index2) const;
        int get_extreme_index(Point point) const;
        void compute_interval(Point point, double& min, double& max) const;
};