#pragma once

#include "line.hpp"
#include "point.hpp"
#include "tools.hpp"
#include "vector.hpp"
#include <iostream>

namespace Geometry {
template <typename FloatType> class Segment {
private:
  Point<FloatType> start_point = Point<FloatType>();
  Point<FloatType> end_point = Point<FloatType>();
  Vector<FloatType> direction_vector = Vector<FloatType>();

public:
  Segment() = default;

  Segment(const Point<FloatType> &point1, const Point<FloatType> &point2)
      : start_point{point1}, end_point{point2} {
    direction_vector = {point2.get_x() - point1.get_x(),
                        point2.get_y() - point1.get_y(),
                        point2.get_z() - point1.get_z()};
  }

  Segment(const Point<FloatType> &point) {
    start_point = point;
    end_point = point;
    direction_vector = {0, 0, 0};
  }

  const Point<FloatType> &get_start_point() const { return start_point; }

  const Point<FloatType> &get_end_point() const { return end_point; }

  const Vector<FloatType> &get_direction_vector() const {
    return direction_vector;
  }

  bool is_point_belong(const Point<FloatType> &point) const {
    return (Line(start_point, end_point).is_point_belong(point) &&
            is_float_in_segment(point.get_x(), start_point.get_x(),
                                end_point.get_x()) &&
            is_float_in_segment(point.get_y(), start_point.get_y(),
                                end_point.get_y()) &&
            is_float_in_segment(point.get_z(), start_point.get_z(),
                                end_point.get_z()));
  }

  bool is_valid() const {
    return (start_point.is_valid() && end_point.is_valid() &&
            !start_point.is_equal(end_point));
  }

  bool is_nan() const { return start_point.is_nan() && end_point.is_nan(); }

  bool is_equal(const Segment &segment) const {
    return (start_point.is_equal(segment.start_point) &&
            end_point.is_equal(segment.end_point)) ||
           (start_point.is_equal(segment.end_point) &&
            end_point.is_equal(segment.start_point));
  }

  void print() const {
    std::cout << "-------------\n";
    std::cout << "Segment:\nstart_point: ";
    start_point.print();
    std::cout << "end_point:";
    end_point.print();
    std::cout << "-------------\n";
  }

  FloatType length() const {
    return std::pow(std::pow(start_point.get_x() - end_point.get_x(), 2) +
                        std::pow(start_point.get_y() - end_point.get_y(), 2) +
                        std::pow(start_point.get_z() - end_point.get_z(), 2),
                    0.5);
  }

  Segment segments_intersection(const Segment &segment) const {
    if (segment.direction_vector.is_collinear(direction_vector)) {
      return collinear_segments_intersection(segment);
    }
    return not_collinear_segments_intersection(segment);
  }

  Segment collinear_segments_intersection(const Segment &segment) const {
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

    return Segment();
  }

  Segment intersection_with_point(const Point<FloatType> &point) const {
    if (is_point_belong(point)) {
      return Segment(point);
    }
    return Segment();
  }

  Segment not_collinear_segments_intersection(const Segment &segment) const {
    if (start_point.is_equal(end_point)) {
      return segment.intersection_with_point(start_point);
    }

    if (segment.start_point.is_equal(segment.end_point)) {
      return intersection_with_point(segment.start_point);
    }

    std::cout << "segment: " << std::endl;

    std::pair<FloatType, FloatType> params_of_intersection =
        solve_system_3eq_2var(
            {start_point.get_x() - end_point.get_x(),
             segment.end_point.get_x() - segment.start_point.get_x(),
             segment.end_point.get_x() - end_point.get_x()},
            {start_point.get_y() - end_point.get_y(),
             segment.end_point.get_y() - segment.start_point.get_y(),
             segment.end_point.get_y() - end_point.get_y()},
            {start_point.get_z() - end_point.get_z(),
             segment.end_point.get_z() - segment.start_point.get_z(),
             segment.end_point.get_z() - end_point.get_z()});

    if (is_nan_solution(params_of_intersection)) {
      return Segment();
    }

    FloatType t = params_of_intersection.first;
    FloatType s = params_of_intersection.second;

    if (is_float_in_segment(t, 0, 1) && is_float_in_segment(s, 0, 1)) {
      return Segment(
          Point(t * start_point.get_x() + (1 - t) * end_point.get_x(),
                t * start_point.get_y() + (1 - t) * end_point.get_y(),
                t * start_point.get_z() + (1 - t) * end_point.get_z()));
    }
    return Segment();
  }
};
} // namespace Geometry