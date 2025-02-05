#pragma once

#include "point.hpp"
#include "tools.hpp"
#include "vector.hpp"
#include <iostream>

namespace Geometry {
template <typename FloatType> class Line {
private:
  Point<FloatType> start_point = Point<FloatType>();
  Vector<FloatType> direction_vector = Vector<FloatType>();

public:
  Line() = default;

  Line(const Point<FloatType> &point1, const Point<FloatType> &point2) {
    start_point = point1;
    direction_vector = {point1, point2};
  }

  Line(const Point<FloatType> &point, const Vector<FloatType> &vector) {
    start_point = point;
    direction_vector = vector;
  }

  const Point<FloatType> &get_start_point() const { return start_point; }

  const Vector<FloatType> &get_direction_vector() const {
    return direction_vector;
  }

  Point<FloatType> lines_intersection(const Line<FloatType> &line) const {
    std::pair<FloatType, FloatType> params_of_intersection =
        solve_system_3eq_2var(
            std::vector<FloatType>{
                direction_vector.get_x(), -line.direction_vector.get_x(),
                line.start_point.get_x() - start_point.get_x()},
            std::vector<FloatType>{
                direction_vector.get_y(), -line.direction_vector.get_y(),
                line.start_point.get_y() - start_point.get_y()},
            std::vector<FloatType>{
                direction_vector.get_z(), -line.direction_vector.get_z(),
                line.start_point.get_z() - start_point.get_z()});

    if (is_nan_solution(params_of_intersection)) {
      return Point<FloatType>();
    }

    else if (is_inf_solution(params_of_intersection)) {
      return Point<FloatType>(INFINITY, INFINITY, INFINITY);
    }

    else {
      return Point<FloatType>{
          start_point.get_x() +
              params_of_intersection.first * direction_vector.get_x(),
          start_point.get_y() +
              params_of_intersection.first * direction_vector.get_y(),
          start_point.get_z() +
              params_of_intersection.first * direction_vector.get_z(),
      };
    }
  }

  bool is_equal(const Line<FloatType> &line) const {
    return line.direction_vector.is_collinear(
               {start_point, line.start_point}) &&
           line.direction_vector.is_collinear(direction_vector);
  }

  bool is_parallel(const Line<FloatType> &line) const {
    return line.direction_vector.is_collinear({start_point, line.start_point});
  }

  bool is_point_belong(const Point<FloatType> &point) const {
    if (solve_system_3eq_2var(
            std::vector<FloatType>{point.get_x(), -direction_vector.get_x(),
                                   start_point.get_x()},
            std::vector<FloatType>{point.get_y(), -direction_vector.get_y(),
                                   start_point.get_y()},
            std::vector<FloatType>{point.get_z(), -direction_vector.get_z(),
                                   start_point.get_z()}) !=
        nan_solution<FloatType>()) {
      return true;
    }
    return false;
  }

  void print() const {
    std::cout << "-------------\n";
    std::cout << "Line:\nstart_point: ";
    start_point.print();
    std::cout << "direction_vector:";
    direction_vector.print();
    std::cout << "-------------\n";
  }
};
} // namespace Geometry