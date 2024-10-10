#pragma once

#include "tools.hpp"
#include "segment.hpp"
#include "vector.hpp"
#include "point.hpp"
#include "plane.hpp"
#include "line.hpp"

namespace Geometry {
    class Triangle {
        private:
            Point a = NAN_POINT;
            Point b = NAN_POINT;
            Point c = NAN_POINT;
            Plane plane = Plane();

            void compute_interval(Point point, double& min, double& max) const;
            bool is_intersect_for_point(const Triangle& triangle) const;
            bool is_intersect_for_segment(const Triangle& triangle) const;
            bool is_intersect_in_same_plane(const Triangle& triangle) const;
            bool is_in_same_half_plane(const Plane& plane) const;
            int get_middle_index(int index1, int index2) const;
            int get_extreme_index(Point point) const;
            Point get_vertice(int number) const;
            Segment intersection_line_in_same_plane(const Line& line) const;
        public:
            Triangle(const Point& point1, const Point& point2, const Point& point3);

            Point get_a() const;
            Point get_b() const;
            Point get_c() const;
            
            bool is_valid() const;
            bool is_point() const;
            bool is_segment() const;
            bool is_equal(const Triangle& triangle) const;
            bool is_point_belong(const Point& point) const;
            bool is_degenerate() const;
            bool is_intersect(const Triangle& triangle) const;
            bool is_intersect_segment(const Segment& segment) const;
    };
}