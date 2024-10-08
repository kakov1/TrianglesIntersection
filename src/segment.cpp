#include "segment.hpp"
#include "tools.hpp"
#include "point.hpp"
#include "line.hpp"
#include <cmath>
#include <iostream>

Geometry::Point Geometry::Segment::get_start_point() const { return start_point; }

Geometry::Point Geometry::Segment::get_end_point() const { return end_point; }

Geometry::Vector Geometry::Segment::get_direction_vector() const { return direction_vector; }

Geometry::Segment::Segment(const Geometry::Point& point1, const Geometry::Point& point2) {
            start_point = point1;
            end_point = point2;
            direction_vector = {point2.get_x() - point1.get_x(),
                                point2.get_y() - point1.get_y(),
                                point2.get_z() - point1.get_z()};
}

Geometry::Segment::Segment(const Geometry::Point& point) {
    start_point = point;
    end_point = point;
    direction_vector = {0, 0, 0};
}

bool Geometry::Segment::is_point_belong(const Geometry::Point& point) const {
    return (Line(start_point, end_point).is_point_belong(point) && 
            is_double_in_segment(point.get_x(), start_point.get_x(), end_point.get_x()) &&
            is_double_in_segment(point.get_y(), start_point.get_y(), end_point.get_y()) &&
            is_double_in_segment(point.get_z(), start_point.get_z(), end_point.get_z()));
}

bool Geometry::Segment::is_valid() const {
    return (start_point.is_valid() && end_point.is_valid() && !start_point.is_equal(end_point));
}

bool Geometry::Segment::is_nan() const {
    return start_point.is_nan() && end_point.is_nan();
}

bool Geometry::Segment::is_equal(const Segment& segment) const {
    return (start_point.is_equal(segment.start_point) && end_point.is_equal(segment.end_point)) ||
           (start_point.is_equal(segment.end_point) && end_point.is_equal(segment.start_point));
}

void Geometry::Segment::print() const {
    std::cout << "-------------\n";
    std::cout << "Segment:\nstart_point: ";
    start_point.print();
    std::cout << "end_point:";
    end_point.print();
    std::cout << "-------------\n";
}

double Geometry::Segment::length() const {
    return pow(pow(start_point.get_x() - end_point.get_x(), 2) +
               pow(start_point.get_y() - end_point.get_y(), 2) +
               pow(start_point.get_z() - end_point.get_z(), 2), 0.5);
}

Geometry::Segment Geometry::Segment::segments_intersection(const Segment& segment) const {
    if (segment.direction_vector.is_collinear(direction_vector)) {
        return collinear_segments_intersection(segment);
    }
    return not_collinear_segments_intersection(segment);

}

Geometry::Segment Geometry::Segment::collinear_segments_intersection(const Segment& segment) const {
    Segment segment_copy = segment;
    if (!direction_vector.is_codirectional(segment.direction_vector)) {
        segment_copy = Segment(segment.end_point, segment.start_point);
    }

    if (is_point_belong(segment_copy.start_point) &&
        is_point_belong(segment_copy.end_point)) {
        return Segment(segment_copy.start_point, segment_copy.end_point);
    }

    if (segment_copy.is_point_belong(start_point) &&
        segment_copy.is_point_belong(end_point)) {
        return Segment(start_point, end_point);
    }

    if ((segment_copy.is_point_belong(end_point) &&
        !segment_copy.is_point_belong(start_point)) ||
        (is_point_belong(segment_copy.start_point) &&
        !is_point_belong(segment_copy.end_point))) {
        return Segment(segment_copy.start_point, end_point);
    }

    if ((segment_copy.is_point_belong(start_point) &&
        !segment_copy.is_point_belong(end_point)) ||
        (is_point_belong(segment_copy.end_point) &&
        !is_point_belong(segment_copy.start_point))) {
        return Segment(start_point, segment_copy.end_point);
    }

    return NAN_SEGMENT;
}

Geometry::Segment Geometry::Segment::intersection_with_point(const Geometry::Point& point) const {
    if (is_point_belong(point)) {
        return Segment(point);
    }
    return NAN_SEGMENT;
}

Geometry::Segment Geometry::Segment::not_collinear_segments_intersection(const Segment& segment) const {
    if (start_point.is_equal(end_point)) {
        return segment.intersection_with_point(start_point);
    }

    if (segment.start_point.is_equal(segment.end_point)) {
        return intersection_with_point(segment.start_point);
    }

    std::pair<double, double> params_of_intersection = 
    solve_system_3eq_2var(Vector(start_point.get_x() - end_point.get_x(),
                           segment.end_point.get_x() - segment.start_point.get_x(),
                           segment.end_point.get_x() - end_point.get_x()),
                          Vector(start_point.get_y() - end_point.get_y(),
                           segment.end_point.get_y() - segment.start_point.get_y(),
                           segment.end_point.get_y() - end_point.get_y()),
                          Vector(start_point.get_z() - end_point.get_z(),
                           segment.end_point.get_z() - segment.start_point.get_z(),
                           segment.end_point.get_z() - end_point.get_z())
                         );
 
    if (is_nan_solution(params_of_intersection)) {
        return NAN_SEGMENT;
    }

    double t = params_of_intersection.first;
    double s = params_of_intersection.second;
    
    if (is_double_in_segment(t, 0, 1) &&
        is_double_in_segment(s, 0, 1)) {
        return Segment(Point(t * start_point.get_x() + (1-t)*end_point.get_x(),
                             t * start_point.get_y() + (1-t)*end_point.get_y(),
                             t * start_point.get_z() + (1-t)*end_point.get_z()));
    }
    return NAN_SEGMENT;
}