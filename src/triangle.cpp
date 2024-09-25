#include "triangle.hpp"
#include "tools.hpp"
#include "segment.hpp"

bool Triangle::is_valid() const {
    return are_points_collinear(a, b, c);
}

bool Triangle::is_in_same_half_plane(const Plane& plane) const {
    return (plane.is_point_over_plane(a) &&
            plane.is_point_over_plane(b) &&
            plane.is_point_over_plane(c)) ||
           (!plane.is_point_over_plane(a) &&
            !plane.is_point_over_plane(b) &&
            !plane.is_point_over_plane(c));
}

Segment Triangle::line_in_same_plane_intersection(const Line& line) const {
    if (line.is_equal({a, b})) {
        return {a, b};
    }
    if (line.is_equal({b, c})) {
        return {b, c};
    }
    if (line.is_equal({a, c})) {
        return {a, c};
    }
    if (line.is_point_belong(a)) {
        if (line.is_intersect({b, c})) {
            
        }
    }
}

bool Triangle::is_intersect(const Triangle& triangle) const {
    if (plane.is_parallel(triangle.plane)) {
        if (plane.is_equal(triangle.plane)) {
            is_intersect_in_same_plane(triangle);
        }
        return false;
    }
    else {
        if (triangle.is_in_same_half_plane(triangle.plane)) {
            return false;
        }
        else {
            //overlap_method();
        }
    }
}