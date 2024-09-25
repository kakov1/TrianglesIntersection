#include "line.hpp"
#include "tools.hpp"
#include "segment.hpp"
#include <iostream>
#include <cassert>

bool Line::is_equal(const Line& line) const {
    return line.direction_vector.is_collinear({start_point, line.start_point}) &&
           line.direction_vector.is_collinear(direction_vector);
}

bool Line::is_parallel(const Line& line) const {
    return line.direction_vector.is_collinear({start_point, line.start_point});
}


Point Line::lines_intersection(const Line& line) const {
    if (is_parallel(line) && !is_equal(line)) {
        return NAN_POINT;
    }
    if (direction_vector.is_skew(line.direction_vector)) {
        return NAN_POINT;
    }
    if (is_equal(line)) {
        return INFINITY_POINT;
    }

    float main_det_xy = det_two(direction_vector.x, -line.direction_vector.x, 
                                direction_vector.y, -line.direction_vector.y);
    float main_det_yz = det_two(direction_vector.y, -line.direction_vector.y, 
                                direction_vector.z, -line.direction_vector.z);
    float main_det_xz = det_two(direction_vector.x, -line.direction_vector.x, 
                                direction_vector.z, -line.direction_vector.z);
    
    std::cout << main_det_xy << " " << main_det_xz << " " << main_det_yz << std::endl;
    if (is_equal_floats(main_det_xy, 0) && is_equal_floats(main_det_xz, 0)&& is_equal_floats(main_det_yz, 0)) {
        return NAN_POINT;
    }
    else {
        float main_det;
        float compl_det;
        if (!is_equal_floats(main_det_xy, 0)) {
            main_det = main_det_xy;
            compl_det = det_two(line.start_point.x - start_point.x, -line.direction_vector.x,
                                line.start_point.y - start_point.y, -line.direction_vector.y);
        }               
        else if (!is_equal_floats(main_det_xz, 0)) {
            main_det = main_det_xz;
            compl_det = det_two(line.start_point.x - start_point.x, -line.direction_vector.x,
                                line.start_point.z - start_point.z, -line.direction_vector.z);
        }
        else if (!is_equal_floats(main_det_yz, 0)) {
            main_det = main_det_yz;
            compl_det = det_two(line.start_point.y - start_point.y, -line.direction_vector.y,
                                line.start_point.z - start_point.z, -line.direction_vector.z);
        }
        else {
            assert("ERROR INTERSECTION");
        }
        float t = compl_det/main_det;
        return {start_point.x + direction_vector.x * t,
                start_point.y + direction_vector.y * t,
                start_point.z + direction_vector.z * t};
    }
}   

bool Line::is_point_belong(const Point& point) const {
    return is_equal_floats((point.x-start_point.x)/direction_vector.x,
                           (point.y-start_point.y)/direction_vector.y) &&
           is_equal_floats((point.y-start_point.y)/direction_vector.y,
                           (point.z-start_point.z)/direction_vector.z);
}