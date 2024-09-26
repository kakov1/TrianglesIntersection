#include "segment.hpp"
#include "tools.hpp"
#include "point.hpp"
#include <cmath>
#include <cassert>
#include <algorithm>

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

bool Segment::is_intersect(const Segment& segment) const {
    assert(is_valid());

    if (!direction_vector.is_collinear(segment.direction_vector)) {
        float main_det = det_two(direction_vector.x, -segment.direction_vector.x,
                                 direction_vector.y, -segment.direction_vector.y);
    }
    return false;
}

bool Segment::is_point_belong(const Point& point) const {
    return pow(det_two(point.x - start_point.x, point.y - start_point.y,
               direction_vector.x, direction_vector.y), 2) +
           pow(det_two(point.y - start_point.y, point.z - start_point.z,
               direction_vector.y, direction_vector.z), 2) +
           pow(det_two(point.x - start_point.x, point.z - start_point.z,
               direction_vector.x, direction_vector.z), 2) == 0 &&
           std::min(start_point.x, end_point.x) < point.x < std::max(start_point.x, end_point.x) &&
           std::min(start_point.y, end_point.y) < point.y < std::max(start_point.y, end_point.y) &&
           std::min(start_point.z, end_point.z) < point.z < std::max(start_point.z, end_point.z);
}

bool Segment::is_valid() const {
    return (start_point.is_valid() && end_point.is_valid() && !start_point.is_equal(end_point));
}

Point Segment::segments_intersection(const Segment& segment) const {
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
    
    if (is_nan_solution(params_of_intersection)) {
        return NAN_POINT;
    }
    else if (is_inf_solution(params_of_intersection)) {
        return INFINITY_POINT;
    }
    else {
        float param = params_of_intersection.first;
        return {param * start_point.x + (1-param)*end_point.x,
                param * start_point.y + (1-param)*end_point.y,
                param * start_point.z + (1-param)*end_point.z,
               };
    }
}