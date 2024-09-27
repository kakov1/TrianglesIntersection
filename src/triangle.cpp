#include "triangle.hpp"
#include "tools.hpp"
#include "segment.hpp"
#include "point.hpp"
#include <iostream>

bool Triangle::is_valid() const {
    return are_points_collinear(a, b, c);
}

bool Triangle::is_in_same_half_plane(const Plane& plane) const {
    return (plane.is_point_over_plane(a) &&
            plane.is_point_over_plane(b) &&
            plane.is_point_over_plane(c)) ||
           (plane.is_point_under_plane(a) &&
            plane.is_point_under_plane(b) &&
            plane.is_point_under_plane(c));
}

Point Triangle::get_vertice(int number) const {
    if (number == 0) {
        return a;
    }
    else if(number == 1) {
        return b;
    }
    else if(number == 2) {
        return c;
    }
    else {
        return NAN_POINT;
    }
}

void Triangle::compute_interval(Point point, double& min, double& max) const {
    min = max = Vector({0, 0, 0}, get_vertice(0)).scalar_product(Vector({0, 0, 0}, point));
    for (int i = 1; i < 3; i++) {
        double value = Vector({0, 0, 0}, get_vertice(i)).scalar_product(Vector({0, 0, 0}, point));
        if (value < min) {
            min = value;
        }
        else if (value > max) {
            max = value;
        }
    }
}

bool Triangle::is_intersect_in_same_plane(const Triangle& triangle) const {
    double min1, max1, min2, max2;
    for (int index1 = 0, index2 = 2; index1 < 3; index2 = index1, index1++) {
        Vector side(get_vertice(index2), get_vertice(index1));
        Vector perp_side = side.find_perp_in_plane(plane);
        compute_interval(Point(perp_side.x, perp_side.y,perp_side.z), min1, max1);
        triangle.compute_interval(Point(perp_side.x, perp_side.y,perp_side.z), min2, max2);
        if (max2 < min1 || max1 < min2) {
            return false;
        }
    }
    for (int index1 = 0, index2 = 2; index1 < 3; index2 = index1, index1++) {
        Vector side(triangle.get_vertice(index2), triangle.get_vertice(index1));
        Vector perp_side = side.find_perp_in_plane(triangle.plane);
        compute_interval(Point(perp_side.x, perp_side.y,perp_side.z), min1, max1);
        triangle.compute_interval(Point(perp_side.x, perp_side.y,perp_side.z), min2, max2);
        if (max2 < min1 || max1 < min2) {
            return false;
        }
    }
    return true;
} 


Segment Triangle::intersection_line_in_same_plane(const Line& line) const {
    if (line.is_equal({a, b})) {
        return {a, b};
    }
    if (line.is_equal({b, c})) {
        return {b, c};
    }
    if (line.is_equal({a, c})) {
        return {a, c};
    }

    //Line({a,b}).print();

    Point intersection_point_ab = line.lines_intersection({a, b});
    Point intersection_point_bc = line.lines_intersection({b, c});
    Point intersection_point_ac = line.lines_intersection({a, c});
    //std::cout<<"DO:\n";
    //intersection_point_ab.print();
    //intersection_point_bc.print();
    //intersection_point_ac.print();

    //std::cout<<Segment(b, c).is_point_belong(intersection_point_bc)<<std::endl;

    if (!Segment(a, b).is_point_belong(intersection_point_ab)) {
        intersection_point_ab = NAN_POINT;
    }
    if (!Segment(b, c).is_point_belong(intersection_point_bc)) {
        intersection_point_bc = NAN_POINT;
    }
    if (!Segment(a, c).is_point_belong(intersection_point_ac)) {
        intersection_point_ac = NAN_POINT;
    }
    //std::cout<<"POSLE:\n";
    //intersection_point_ab.print();
    //intersection_point_bc.print();
    //intersection_point_ac.print();

    if (!intersection_point_ab.is_equal(NAN_POINT) &&
        !intersection_point_bc.is_equal(NAN_POINT)) {
        return {intersection_point_ab, intersection_point_bc};
    }
    else if (!intersection_point_bc.is_equal(NAN_POINT) &&
             !intersection_point_ac.is_equal(NAN_POINT)) {
        return {intersection_point_bc, intersection_point_ac};
    }
    else if (!intersection_point_ab.is_equal(NAN_POINT) &&
             !intersection_point_ac.is_equal(NAN_POINT)) {
        return {intersection_point_ab, intersection_point_ac};
    }
    return NAN_SEGMENT;
}

bool Triangle::is_intersect(const Triangle& triangle) const {
    if (plane.is_collinear(triangle.plane)) {
        if (plane.is_equal(triangle.plane)) {
            return is_intersect_in_same_plane(triangle);
        }
        return false;
    }
    else {
        if (triangle.is_in_same_half_plane(triangle.plane)) {
            return false;
        }
        else {
            Line intersection_line = plane.intersection(triangle.plane);

            //intersection_line.print();

            Segment segment1 = intersection_line_in_same_plane(intersection_line);
            Segment segment2 = triangle.intersection_line_in_same_plane(intersection_line);

            //segment1.print();
            //segment2.print();
            //segment1.segments_intersection(segment2).print();
            if (
                !(segment1.segments_intersection(segment2).is_equal(NAN_POINT))) {
                return true;
            }
            return false;
        }
    }
}