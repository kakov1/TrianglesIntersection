#include "segment.hpp"
#include "tools.hpp"
#include "point.hpp"
#include "line.hpp"
#include <cmath>
#include <cassert>
#include <algorithm>
#include <variant>
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
            is_double_in_segment(point.x, start_point.x, end_point.x) &&
            is_double_in_segment(point.y, start_point.y, end_point.y) &&
            is_double_in_segment(point.z, start_point.z, end_point.z));
}

bool Segment::is_valid() const {
    return (start_point.is_valid() && end_point.is_valid() && !start_point.is_equal(end_point));
}

bool Segment::is_nan() const {
    return start_point.is_nan() && end_point.is_nan();
}

bool Segment::is_equal(const Segment& segment) const {
    return (start_point.is_equal(segment.start_point) && end_point.is_equal(segment.end_point)) ||
           (start_point.is_equal(segment.end_point) && end_point.is_equal(segment.start_point));
}

void Segment::print() const {
    std::cout << "-------------\n";
    std::cout << "Segment:\nstart_point: ";
    start_point.print();
    std::cout << "end_point:";
    end_point.print();
    std::cout << "-------------\n";
}

double Segment::length() const {
    return pow(pow(start_point.x - end_point.x, 2) +
               pow(start_point.y - end_point.y, 2) +
               pow(start_point.z - end_point.z, 2), 0.5);
}

Segment Segment::segments_intersection(const Segment& segment) const {
    if (segment.direction_vector.is_collinear(direction_vector)) {
        return collinear_segments_intersection(segment);
    }
    return not_collinear_segments_intersection(segment);

}

Segment Segment::collinear_segments_intersection(const Segment& segment) const {
    Segment segment_copy = segment;
    if (!direction_vector.is_codirectional(segment.direction_vector)) {
        segment_copy = Segment(segment.end_point, segment.start_point);
    }
    //std::cout << "----------------------" <<std::endl;
    //print();
    //segment.print();
    //segment_copy.print();

    if (is_point_belong(segment_copy.start_point)) {
        //std::cout<<"1"<<std::endl;
        if (is_point_belong(segment_copy.end_point)) {
            return Segment(segment_copy.start_point, segment_copy.end_point);
        }
        return Segment(segment_copy.start_point, end_point);
    }
    if (is_point_belong(segment_copy.end_point)) {
        //std::cout<<"2"<<std::endl;
        if (is_point_belong(segment_copy.start_point)) {
            return Segment(segment_copy.start_point, segment_copy.end_point);
        }
        return Segment(start_point, segment_copy.end_point);
    }
    if (segment_copy.is_point_belong(start_point)) {
        //std::cout<<"3"<<std::endl;
        if (segment_copy.is_point_belong(end_point)) {
            return Segment(start_point, end_point);
        }
        return Segment(start_point, segment_copy.end_point);
    }
    if (segment_copy.is_point_belong(end_point)) {
        std::cout<<"4"<<std::endl;
        if (segment_copy.is_point_belong(start_point)) {
            return Segment(start_point, end_point);
        }
        return Segment(segment_copy.start_point, end_point);
    }
    return NAN_SEGMENT;
}

Segment Segment::not_collinear_segments_intersection(const Segment& segment) const {
    if (start_point.is_equal(end_point)) {
        if (segment.is_point_belong(start_point)) {
            return Segment(start_point);
        } 
        return NAN_SEGMENT;
    }
    if (segment.start_point.is_equal(segment.end_point)) {
        if (is_point_belong(segment.start_point)) {
            return Segment(segment.start_point);
        }
        return NAN_SEGMENT;
    }
    //std::cout<<"from seg_inter:\n";
    std::pair<double, double> params_of_intersection = 
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
        return NAN_SEGMENT;
    }
    double t = params_of_intersection.first;
    double s = params_of_intersection.second;
    //std::cout<< is_double_in_segment(t, 0, 1) << " " << is_double_in_segment(s, 0, 1)<<std::endl;
    if (is_double_in_segment(t, 0, 1) &&
        is_double_in_segment(s, 0, 1)) {
        return Segment(Point(t * start_point.x + (1-t)*end_point.x,
                t * start_point.y + (1-t)*end_point.y,
                t * start_point.z + (1-t)*end_point.z));
    }
    return NAN_SEGMENT;
}