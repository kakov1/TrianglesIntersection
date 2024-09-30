#include "tools.hpp"
#include "vector.hpp"
#include <utility>
#include <iostream>
#include <algorithm>
#include <cmath>

bool is_equal_doubles(const double a, const double b) {
    return (std::fabs(a - b) < EPSILON);
}

double is_zero(const double a) {
    return is_equal_doubles(a, 0)?0:a;
}

bool is_double_in_segment(double number, double a, double b) {
    return (std::min(a, b) < number) && (number < std::max(a, b)) ||
           is_equal_doubles(number, a) || is_equal_doubles(number, b);
}

double det_two(const double a11, const double a12, const double a21, const double a22) {
    return a11 * a22 - a21 * a12;
}

bool are_points_collinear(const Point& point1, const Point& point2, const Point& point3) {
    Vector side1(point1, point2);
    Vector side2(point2, point3);
    
    return (side1.is_collinear(side2));
}

char sign(double number) {
    return number<0?'-':'+';
}

std::pair<double, double> solve_system_2eq_2var(const Vector& row1, const Vector& row2) {
    double main_det = det_two(row1.x, row1.y,
                             row2.x, row2.y);
    double x_det = det_two(row1.z, row1.y,
                          row2.z, row2.y);
    double y_det = det_two(row1.x, row1.z,
                          row2.x, row2.z);

    //std::cout<<"2eq_2var\n";
    //std::cout <<main_det << " " << x_det << " " << y_det << std::endl;
    
    if (is_equal_doubles(main_det, 0)) {
        if (is_equal_doubles(x_det, 0) && is_equal_doubles(y_det, 0)) {
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

bool is_nan_solution(std::pair<double, double> solution) {
    return std::isnan(solution.first) && std::isnan(solution.second);
}

bool is_inf_solution(std::pair<double, double> solution) {
    return std::isinf(solution.first) && std::isinf(solution.second);
}

bool is_equal_solutions(std::pair<double, double> solution1, std::pair<double, double> solution2) {
    return is_equal_doubles(solution1.first, solution2.first) &&
           is_equal_doubles(solution1.second, solution2.second);
}

std::pair<double, double> solve_system_3eq_2var(const Vector& row1, const Vector& row2, const Vector& row3) {
    std::pair<double, double> solution12 = solve_system_2eq_2var(row1, row2);
    std::pair<double, double> solution23 = solve_system_2eq_2var(row2, row3);
    std::pair<double, double> solution13 = solve_system_2eq_2var(row1, row3);

    //std::cout <<"Solutions:\n";
    //row1.print();
    //row2.print();
    //row3.print();
    //std::cout << solution12.first << " " << solution12.second << std::endl;
    //std::cout << solution23.first << " " << solution23.second << std::endl;
    //std::cout << solution13.first << " " << solution13.second << std::endl;
    //std::cout << is_equal_solutions(solution12, solution13)<< std::endl;
    //std::cout << "-------------------------------------------\n";

    if (is_inf_solution(solution12) &&
        is_inf_solution(solution23) &&
        is_inf_solution(solution13)) {
        return INFINITY_SOLUTION;
    }
    if (is_inf_solution(solution12) &&
        is_inf_solution(solution23)) {
        return solution13;
    }
        if (is_inf_solution(solution12) &&
            is_inf_solution(solution13)) {
        return solution23;
    }
    if (is_inf_solution(solution23) &&
        is_inf_solution(solution13)) {
        return solution12;
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
    if (is_equal_solutions(solution12, solution13) &&
        is_equal_solutions(solution12, solution23)) {
            //std::cout<<"asdadsadsdqwddqwd\n";
            //std::cout << solution12.first << " " << solution12.second << std::endl;
            return solution12;
    }
    else {
        //std::cout << "kvakva\n"<<std::endl;
        return NAN_SOLUTION;
    }
}