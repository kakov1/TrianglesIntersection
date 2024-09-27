#include "segment.hpp"
#include "tools.hpp"
#include "point.hpp"
#include "line.hpp"
#include <cmath>
#include <cassert>
#include <algorithm>
#include <iostream>

bool Segment::is_on_same_line(const Segment& segment) const {
    assert(is_valid());

    if (direction_vector.is_collinear(segment.direction_vector)) {
        Vector connection_origins = {start_point.x - segment.start_point.x,
                                     start_point.y - segment.start_point.y,
                                     start_point.z - segment.start_point.z};
        connection_origins.normalize();

        return (direction_vector.is_equal(connection_origins) ||
                direction_vector.is_equal(connection_origins.opposite()));
    }

    return false;
}

bool Segment::is_point_belong(const Point& point) const {
    return (Line(start_point, end_point).is_point_belong(point) && 
            is_float_in_segment(point.x, start_point.x, end_point.x) &&
            is_float_in_segment(point.y, start_point.y, end_point.y) &&
            is_float_in_segment(point.z, start_point.z, end_point.z));
}

bool Segment::is_valid() const {
    return (start_point.is_valid() && end_point.is_valid() && !start_point.is_equal(end_point));
}

bool Segment::is_nan() const {
    return start_point.is_nan() && end_point.is_nan();
}

void Segment::print() const {
    std::cout << "-------------\n";
    std::cout << "Segment:\nstart_point: ";
    start_point.print();
    std::cout << "end_point:";
    end_point.print();
    std::cout << "-------------\n";
}

Point Segment::segments_intersection(const Segment& segment) const {
    //std::cout <<"sdasdadsadsdasd\n";
    if (start_point.is_equal(end_point)) {
        if (segment.is_point_belong(start_point)) {
            return start_point;
        } 
        return NAN_POINT;
    }
    if (segment.start_point.is_equal(segment.end_point)) {
        if (is_point_belong(segment.start_point)) {
            return segment.start_point;
        }
        return NAN_POINT;
    }
    //std::cout<<"from inter:\n";
    std::pair<float, float> params_of_intersection = 
    solve_system_3eq_2var({start_point.x - end_point.x,
                           segment.end_point.x - segment.start_point.x,
                           segment.end_point.x - end_point.x},
                          {start_point.y - end_point.y,
                           segment.end_point.y - segment.start_point.y,
                           segment.end_point.y - end_point.y},
                          {start_point.z - end_point.z,
                           segment.end_point.z - segment.start_point.z,
                           segment.end_point.z - end_point.z}
                         );
    //std::cout << params_of_intersection.first << " " << params_of_intersection.second<<std::endl;
    if (is_nan_solution(params_of_intersection)) {
        return NAN_POINT;
    }
    else if (is_inf_solution(params_of_intersection)) {
        return INFINITY_POINT;
    }
    else {
        float t = params_of_intersection.first;
        float s = params_of_intersection.second;
        //std::cout<< is_float_in_segment(t, 0, 1) << " " << is_float_in_segment(s, 0, 1)<<std::endl;
        if (is_float_in_segment(t, 0, 1) &&
            is_float_in_segment(s, 0, 1)) {
            return {t * start_point.x + (1-t)*end_point.x,
                    t * start_point.y + (1-t)*end_point.y,
                    t * start_point.z + (1-t)*end_point.z};
        }
        return NAN_POINT;
    }
}