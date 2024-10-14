#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "tools.hpp"
#include <iostream>

namespace Geometry {
    class Line {
        private:
            Point start_point       = Point();
            Vector direction_vector = Vector();

        public:
            Line(){};

            Line(const Point& point1, const Point& point2) {
                start_point      = point1;
                direction_vector = { point1, point2 };
            }

            Line(const Point& point, const Vector& vector) {
                start_point      = point;
                direction_vector = vector;
            }

            Point get_start_point() const {
                return start_point;
            }

            Vector get_direction_vector() const {
                return direction_vector;
            }

            Point lines_intersection(const Line& line) const {
                std::pair<double, double> params_of_intersection = solve_system_3eq_2var(
                { direction_vector.get_x(), -line.direction_vector.get_x(),
                line.start_point.get_x() - start_point.get_x() },
                { direction_vector.get_y(), -line.direction_vector.get_y(),
                line.start_point.get_y() - start_point.get_y() },
                { direction_vector.get_z(), -line.direction_vector.get_z(),
                line.start_point.get_z() - start_point.get_z() });

                if (is_nan_solution(params_of_intersection)) {
                    return Point();
                }

                else if (is_inf_solution(params_of_intersection)) {
                    return Point(INFINITY, INFINITY, INFINITY);
                }

                else {
                    return {
                        start_point.get_x() +
                        params_of_intersection.first * direction_vector.get_x(),
                        start_point.get_y() +
                        params_of_intersection.first * direction_vector.get_y(),
                        start_point.get_z() +
                        params_of_intersection.first * direction_vector.get_z(),
                    };
                }
            }

            bool is_equal(const Line& line) const {
                return line.direction_vector.is_collinear({ start_point, line.start_point }) &&
                line.direction_vector.is_collinear(direction_vector);
            }

            bool is_parallel(const Line& line) const {
                return line.direction_vector.is_collinear({ start_point, line.start_point });
            }

            bool is_point_belong(const Point& point) const {
                if (solve_system_3eq_2var(
                    { point.get_x(), -direction_vector.get_x(), start_point.get_x() },
                    { point.get_y(), -direction_vector.get_y(), start_point.get_y() },
                    { point.get_z(), -direction_vector.get_z(), start_point.get_z() }) !=
                NAN_SOLUTION) {
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
}