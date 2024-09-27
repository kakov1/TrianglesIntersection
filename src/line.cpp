#include "line.hpp"
#include "tools.hpp"
#include "segment.hpp"
#include <cassert>
#include <iostream>

bool Line::is_equal(const Line& line) const {
    return line.direction_vector.is_collinear({start_point, line.start_point}) &&
           line.direction_vector.is_collinear(direction_vector);
}

bool Line::is_parallel(const Line& line) const {
    return line.direction_vector.is_collinear({start_point, line.start_point});
}


Point Line::lines_intersection(const Line& line) const {
    std::pair<float, float> params_of_intersection = 
    solve_system_3eq_2var({direction_vector.x, -line.direction_vector.x,
                           line.start_point.x - start_point.x},
                           {direction_vector.y, -line.direction_vector.y,
                           line.start_point.y - start_point.y},
                           {direction_vector.z, -line.direction_vector.z,
                           line.start_point.z - start_point.z}
                         );
    
    if (is_nan_solution(params_of_intersection)) {
        return NAN_POINT;
    }
    else if (is_inf_solution(params_of_intersection)) {
        return INFINITY_POINT;
    }
    else {
        return {start_point.x + params_of_intersection.first*direction_vector.x,
                start_point.y + params_of_intersection.first*direction_vector.y,
                start_point.z + params_of_intersection.first*direction_vector.z,
               };
    }
}   

bool Line::is_point_belong(const Point& point) const {
    if (solve_system_3eq_2var(Vector(point.x, -direction_vector.x, start_point.x),
                              Vector(point.y, -direction_vector.y, start_point.y),
                              Vector(point.z, -direction_vector.z, start_point.z))
                               != NAN_SOLUTION) {
        return true;
    }
    return false;
}

void Line::print() const {
    std::cout << "-------------\n";
    std::cout << "Line:\nstart_point: ";
    start_point.print();
    std::cout << "direction_vector:";
    direction_vector.print();
    std::cout << "-------------\n";
}