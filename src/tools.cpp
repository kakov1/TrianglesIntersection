#include "tools.hpp"
#include "vector.hpp"
#include <utility>

bool is_equal_floats(const float a, const float b) {
    return (fabs(a - b) < EPSILON);
}

float det_two(const float a11, const float a12, const float a21, const float a22) {
    return a11 * a22 - a21 * a12;
}

bool are_points_collinear(const Point& point1, const Point& point2, const Point& point3) {
    Vector side1(point1, point2);
    Vector side2(point2, point3);
    
    return (!side1.is_collinear(side2));
}

char sign(float number) {
    return number<0?'-':'+';
}

std::pair<float, float> solve_system_2eq_2var(const Vector& row1, const Vector& row2) {
    float main_det = det_two(row1.x, row1.y,
                             row2.x, row2.y);
    float x_det = det_two(row1.z, row1.y,
                          row2.z, row2.y);
    float y_det = det_two(row1.x, row1.z,
                          row2.x, row2.z);
    
    if (is_equal_floats(main_det, 0)) {
        if (is_equal_floats(x_det, 0) && is_equal_floats(y_det, 0)) {
            return {INFINITY, INFINITY};
        }
        else {
            return {NAN, NAN};
        }
    }
    else {
        return {x_det/main_det, y_det/main_det};
    }
}

bool is_nan_solution(std::pair<float, float> solution) {
    return std::isnan(solution.first) && std::isnan(solution.second);
}

bool is_inf_solution(std::pair<float, float> solution) {
    return std::isinf(solution.first) && std::isinf(solution.second);
}

std::pair<float, float> solve_system_3eq_2var(const Vector& row1, const Vector& row2, const Vector& row3) {
    std::pair<float, float> solution12 = solve_system_2eq_2var(row1, row2);
    std::pair<float, float> solution23 = solve_system_2eq_2var(row2, row3);
    std::pair<float, float> solution13 = solve_system_2eq_2var(row1, row3);

    if (is_inf_solution(solution12) &&
        is_inf_solution(solution23) &&
        is_inf_solution(solution13)) {
        return INFINITY_SOLUTION;
    }
    if (is_inf_solution(solution12)) {
        return solution23;
    }
    if (is_inf_solution(solution23)) {
        return solution13;
    }
    if (is_inf_solution(solution13)) {
        return solution12;
    }
    if (solution12 == solution23 &&
        solution12 == solution13) {
            return solution12;
    }
    else {
        return NAN_SOLUTION;
    }
}