#pragma once

#include "point.hpp"
#include "vector.hpp"

namespace Geometry {
class Segment {
    private:
        Geometry::Point start_point;
        Geometry::Point end_point;
        Vector direction_vector;
    public:
        Segment() {};
        Segment(const Geometry::Point& point1, const Geometry::Point& point2);
        Segment(const Geometry::Point& point);

        Geometry::Point get_start_point() const;
        Geometry::Point get_end_point() const;
        Vector get_direction_vector() const;

        void print() const;
        bool is_point_belong(const Geometry::Point& point) const;
        bool is_valid() const;
        bool is_nan() const;
        bool is_equal(const Segment& segment) const;
        double length() const;
        Segment segments_intersection(const Segment& segment) const;
        Segment not_collinear_segments_intersection(const Segment& segment) const;
        Segment collinear_segments_intersection(const Segment& segment) const;
        Segment intersection_with_point(const Geometry::Point& point) const;
};
}