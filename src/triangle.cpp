#include "triangle.hpp"
#include "tools.hpp"
#include "segment.hpp"
#include "point.hpp"
#include <iostream>

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

Segment Triangle::intersection_line_in_same_plane(const Line& line) const {
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
        Point intersection_point = line.lines_intersection({b, c});
        if (!intersection_point.is_equal(NAN_POINT)) {
            return {a, intersection_point};
        }
        else {
            return {a, a};
        }
    }
    if (line.is_point_belong(b)) {
        Point intersection_point = line.lines_intersection({a, c});
        if (!intersection_point.is_equal(NAN_POINT)) {
            return {b, intersection_point};
        }
        else {
            return {b, b};
        }
    }
    if (line.is_point_belong(c)) {
        Point intersection_point = line.lines_intersection({a, b});
        if (!intersection_point.is_equal(NAN_POINT)) {
            return {c, intersection_point};
        }
        else {
            return {c, c};
        }
    }
    Point intersection_point_ab = line.lines_intersection({a, b});
    Point intersection_point_bc = line.lines_intersection({b, c});
    Point intersection_point_ac = line.lines_intersection({a, c});

    if (!intersection_point_ab.is_equal(NAN_POINT) &&
        !intersection_point_bc.is_equal(NAN_POINT)) {
        return {intersection_point_ab, intersection_point_bc};
    }
    else if (!intersection_point_bc.is_equal(NAN_POINT) &&
        !intersection_point_ac.is_equal(NAN_POINT)) {
        return {intersection_point_bc, intersection_point_ac};
    }
    else if (!intersection_point_ab.is_equal(NAN_POINT) &&
        !intersection_point_ac.is_equal(NAN_POINT)) {
        return {intersection_point_ab, intersection_point_ac};
    }
    return {{0, 0, 0}, {0, 0, 0}};
}

bool Triangle::is_intersect(const Triangle& triangle) const {
    if (plane.is_collinear(triangle.plane)) {
        if (plane.is_equal(triangle.plane)) {
            //is_intersect_in_same_plane(triangle);
        }
        return false;
    }
    else {
        if (triangle.is_in_same_half_plane(triangle.plane)) {
            return false;
        }
        else {
            Line intersection_line = plane.intersection(triangle.plane);
            Segment segment1 = intersection_line_in_same_plane(intersection_line);
            Segment segment2 = triangle.intersection_line_in_same_plane(intersection_line);
            if (!segment1.segments_intersection(segment2).is_equal(NAN_POINT)) {
                return true;
            }
            return false;
        }
    }
}