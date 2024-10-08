#pragma once

#include "segment.hpp"
#include "vector.hpp"
#include "point.hpp"
#include "plane.hpp"
#include "line.hpp"

namespace Geometry {
class Triangle {
    private:
        Point a;
        Point b;
        Point c;
        Plane plane;

        void compute_interval(Geometry::Point point, double& min, double& max) const;
        bool is_intersect_for_point(const Triangle& triangle) const;
        bool is_intersect_for_segment(const Triangle& triangle) const;
        bool is_intersect_in_same_plane(const Triangle& triangle) const;
        bool is_in_same_half_plane(const Geometry::Plane& plane) const;
        int get_middle_index(int index1, int index2) const;
        int get_extreme_index(Geometry::Point point) const;
        Geometry::Point get_vertice(int number) const;
        Geometry::Segment intersection_line_in_same_plane(const Geometry::Line& line) const;
    public:
        Triangle(const Geometry::Point& point1, const Geometry::Point& point2, const Geometry::Point& point3);

        Geometry::Point get_a() const;
        Geometry::Point get_b() const;
        Geometry::Point get_c() const;
        
        bool is_valid() const;
        bool is_point() const;
        bool is_segment() const;
        bool is_equal(const Triangle& triangle) const;
        bool is_point_belong(const Geometry::Point& point) const;
        bool is_degenerate() const;
        bool is_intersect(const Triangle& triangle) const;
        bool is_intersect_segment(const Geometry::Segment& segment) const;
};
}