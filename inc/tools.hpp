#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>
#include <iostream>

namespace Geometry {
    template <typename FloatType>
    class Accuracy {
        public:
            static FloatType get_epsilon() { return 1e-8; }

            static std::pair<FloatType, FloatType> nan_solution() {
                return {static_cast<FloatType>(NAN),
                        static_cast<FloatType>(NAN)};
            }

            static std::pair<FloatType, FloatType> inf_solution() {
                return {static_cast<FloatType>(INFINITY),
                        static_cast<FloatType>(INFINITY)};
            }
    };

    template <>
    class Accuracy<long double> {
        public:
            static long double get_epsilon() { return 1e-10; }

            static std::pair<long double, long double> nan_solution() {
                return {static_cast<long double>(NAN),
                        static_cast<long double>(NAN)};
            }

            static std::pair<long double, long double> inf_solution() {
                return {static_cast<long double>(INFINITY),
                        static_cast<long double>(INFINITY)};
            }
    };

    template <>
    class Accuracy<double> {
        public:
            static double get_epsilon() { return 1e-8; }

            static std::pair<double, double> nan_solution() {
                return {NAN, NAN};
            }

            static std::pair<double, double> inf_solution() {
                return {INFINITY, INFINITY};
            }
    };

    template <>
    class Accuracy<float> {
        public:
            static float get_epsilon() { return 1e-5; }

            static std::pair<float, float> nan_solution() {
                return {static_cast<float>(NAN), static_cast<float>(NAN)};
            }

            static std::pair<float, float> inf_solution() {
                return {static_cast<float>(INFINITY),
                        static_cast<float>(INFINITY)};
            }
    };

    template <typename FloatType>
    bool is_equal_floats(FloatType a, FloatType b) {
        return (std::fabs(a - b) < Accuracy<FloatType>::get_epsilon());
    }

    template <typename FloatType>
    bool is_zero(FloatType a) {
        return (std::fabs(a) < Accuracy<FloatType>::get_epsilon());
    }

    template <typename FloatType>
    bool is_bigger(FloatType a, FloatType b) {
        return (!is_equal_floats(a, b) && a - b > Accuracy<FloatType>::get_epsilon());
    }

    template <typename FloatType>
    bool is_bigger_zero(FloatType a) {
        return (a > Accuracy<FloatType>::get_epsilon());
    }

    template <typename FloatType>
    bool is_less(FloatType a, FloatType b) {
        return (!is_equal_floats(a, b) && a - b < -Accuracy<FloatType>::get_epsilon());
    }

    template <typename FloatType>
    bool is_less_zero(FloatType a) {
        return (a < -Accuracy<FloatType>::get_epsilon());
    }

    template <typename FloatType>
    bool is_float_in_segment(FloatType number, FloatType a, FloatType b) {
        return (is_less(std::min(a, b), number)) && (is_less(number, std::max(a, b))) ||
               is_equal_floats(number, a) || is_equal_floats(number, b);
    }

    template <typename FloatType>
    FloatType det_two(FloatType a11, FloatType a12,
                      FloatType a21, FloatType a22) {
        return a11 * a22 - a21 * a12;
    }

    template <typename FloatType>
    char sign(FloatType number) {
        return is_less_zero(number) ? '-' : '+';
    }

    template <typename FloatType>
    std::pair<FloatType, FloatType>
    solve_system_2eq_2var(const std::vector<FloatType>& row1,
                          const std::vector<FloatType>& row2) {
        FloatType main_det = det_two(row1[0], row1[1], row2[0], row2[1]);
        FloatType x_det = det_two(row1[2], row1[1], row2[2], row2[1]);
        FloatType y_det = det_two(row1[0], row1[2], row2[0], row2[2]);

        if (is_zero(main_det)) {
            if (is_zero(x_det) && is_zero(y_det)) {
                return Accuracy<FloatType>::inf_solution();
            }
            else {
                return Accuracy<FloatType>::nan_solution();
            }
        }
        else {
            return {x_det / main_det, y_det / main_det};
        }
    }

    template <typename FloatType>
    bool is_nan_solution(std::pair<FloatType, FloatType> solution) {
        return std::isnan(solution.first) && std::isnan(solution.second);
    }

    template <typename FloatType>
    bool is_inf_solution(std::pair<FloatType, FloatType> solution) {
        return std::isinf(solution.first) && std::isinf(solution.second);
    }

    template <typename FloatType>
    bool is_equal_solutions(std::pair<FloatType, FloatType> solution1,
                            std::pair<FloatType, FloatType> solution2) {
        return std::fabs(solution1.first - solution2.first) < 0.5 &&
               std::fabs(solution1.second - solution2.second) < 0.5;
    }

    template <typename FloatType>
    std::pair<FloatType, FloatType>
    solve_system_3eq_2var(const std::vector<FloatType>& row1,
                          const std::vector<FloatType>& row2,
                          const std::vector<FloatType>& row3) {
        std::pair<FloatType, FloatType> solution12 =
            solve_system_2eq_2var(row1, row2);
        std::pair<FloatType, FloatType> solution23 =
            solve_system_2eq_2var(row2, row3);
        std::pair<FloatType, FloatType> solution13 =
            solve_system_2eq_2var(row1, row3);

        //std::cout << "solutions:" << std::endl;
        //std::cout << solution12.first << " " << solution12.second <<std::endl;
        //std::cout << solution23.first << " " << solution23.second <<std::endl;
        //std::cout << solution13.first << " " << solution13.second <<std::endl;
        //std::cout << "-------------" << std::endl;

        //std::cout << std::fabs(solution12.first - solution23.first) << std::endl;

        if (is_inf_solution(solution12) && is_inf_solution(solution23) &&
            is_inf_solution(solution13))
            return Accuracy<FloatType>::inf_solution();

        if (is_inf_solution(solution12) && is_inf_solution(solution23))
            return solution13;

        if (is_inf_solution(solution12) && is_inf_solution(solution13))
            return solution23;

        if (is_inf_solution(solution23) && is_inf_solution(solution13))
            return solution12;

        if (is_inf_solution(solution12))
            return solution23;

        if (is_inf_solution(solution23))
            return solution13;

        if (is_inf_solution(solution13))
            return solution12;

        if (is_equal_solutions(solution12, solution13) &&
            is_equal_solutions(solution12, solution23)) {
            return solution12;
        }
        else {
            return Accuracy<FloatType>::nan_solution();
        }
    }
} // namespace Geometry