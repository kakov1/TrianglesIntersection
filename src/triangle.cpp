#include "triangle.hpp"
#include "tools.hpp"
#include <iostream>

Geometry::Point Geometry::Triangle::get_a() const { return a; }
Geometry::Point Geometry::Triangle::get_b() const { return b; }
Geometry::Point Geometry::Triangle::get_c() const { return c; }

Geometry::Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3) {
    a = point1;
    b = point2;
    c = point3;
    if (is_segment() && !is_point()) {
        if (!a.is_equal(b) && !b.is_equal(c) && !a.is_equal(c)) {
            if (Segment(a, b).is_point_belong(c)) {
                b = point3;
                c = point2;
            }
            else if (Segment(b, c).is_point_belong(a)) {
                b = point1;
                a = point2;
            }
        }    
    }
    if (is_degenerate()) {
        plane = {NAN_POINT, NAN_POINT, NAN_POINT};
        return;
    }
    plane = Plane(a, b, c);
}

bool Geometry::Triangle::is_valid() const {
    return a.are_points_collinear(b, c);
}

bool Geometry::Triangle::is_degenerate() const {
    return is_point() || is_segment();
}
 
bool Geometry::Triangle::is_point() const {
    return a.is_equal(b) && b.is_equal(c);
}

bool Geometry::Triangle::is_segment() const {
    return a.are_points_collinear(b, c);
}

bool Geometry::Triangle::is_equal(const Triangle& triangle) const {
    return a.is_equal(triangle.a);
}

bool Geometry::Triangle::is_in_same_half_plane(const Plane& plane) const {
    return (plane.is_point_over_plane(a) &&
            plane.is_point_over_plane(b) &&
            plane.is_point_over_plane(c)) ||
           (plane.is_point_under_plane(a) &&
            plane.is_point_under_plane(b) &&
            plane.is_point_under_plane(c));
}

Geometry::Point Geometry::Triangle::get_vertice(int number) const {
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

void Geometry::Triangle::compute_interval(Point point, double& min, double& max) const {
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

bool Geometry::Triangle::is_point_belong(const Point& point) const {
    if (!plane.is_point_belong(point)) {
        return false;
    }
    Vector v0(a, c);
    Vector v1(a, b);
    Vector v2(a, point);

    double dot00 = v0.scalar_product(v0);
    double dot01 = v0.scalar_product(v1);
    double dot02 = v0.scalar_product(v2);
    double dot11 = v1.scalar_product(v1);
    double dot12 = v1.scalar_product(v2);

    double denom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * denom;
    double v = (dot00 * dot12 - dot01 * dot02) * denom;

    return (u > 0 || is_equal_doubles(u, 0)) && (v > 0 || is_equal_doubles(v, 0)) &&
           (u + v < 1 || is_equal_doubles(u + v, 1));
}

bool Geometry::Triangle::is_intersect_in_same_plane(const Triangle& triangle) const {
    double min1, max1, min2, max2;

    for (int index1 = 0, index2 = 2; index1 < 3; index2 = index1, index1++) {
        Vector side(get_vertice(index2), get_vertice(index1));
        Vector perp_side = plane.find_perp_in_plane(side);

        compute_interval(Point(perp_side.get_x(),
                               perp_side.get_y(),
                               perp_side.get_z()), min1, max1);
        triangle.compute_interval(Point(perp_side.get_x(),
                                        perp_side.get_y(),
                                        perp_side.get_z()), min2, max2);
        if (max2 < min1 || max1 < min2) {
            return false;
        }
    }
    for (int index1 = 0, index2 = 2; index1 < 3; index2 = index1, index1++) {
        Vector side(triangle.get_vertice(index2), triangle.get_vertice(index1));
        Vector perp_side = triangle.plane.find_perp_in_plane(side);

        compute_interval(Point(perp_side.get_x(),
                               perp_side.get_y(),
                               perp_side.get_z()), min1, max1);
        triangle.compute_interval(Point(perp_side.get_x(),
                                        perp_side.get_y(),
                                        perp_side.get_z()), min2, max2);
        if (max2 < min1 || max1 < min2) {
            return false;
        }
    }

    return true;
} 


Geometry::Segment Geometry::Triangle::intersection_line_in_same_plane(const Line& line) const {
    if (line.is_equal({a, b})) {
        return {a, b};
    }
    if (line.is_equal({b, c})) {
        return {b, c};
    }
    if (line.is_equal({a, c})) {
        return {a, c};
    }

    Point intersection_point_ab = line.lines_intersection({a, b});
    Point intersection_point_bc = line.lines_intersection({b, c});
    Point intersection_point_ac = line.lines_intersection({a, c});

    if (!Segment(a, b).is_point_belong(intersection_point_ab)) {
        intersection_point_ab = NAN_POINT;
    }
    if (!Segment(b, c).is_point_belong(intersection_point_bc)) {
        intersection_point_bc = NAN_POINT;
    }
    if (!Segment(a, c).is_point_belong(intersection_point_ac)) {
        intersection_point_ac = NAN_POINT;
    }

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

bool Geometry::Triangle::is_intersect_segment(const Segment& segment) const {
    Vector e1 = Vector(a, b), e2 = Vector(a, c);
    Vector p = segment.get_direction_vector().vector_product(e2);
    double tmp = p.scalar_product(e1);

    if (tmp > -EPSILON && tmp < EPSILON) {
        return false;
    }

    tmp = 1 / tmp;
    Vector s = Vector(a, segment.get_start_point());

    double u = tmp * s.scalar_product(p);
    if (u < 0 || u > 1) {
        return false;
    } 

    Vector q = s.vector_product(e1);
    double v = tmp * q.scalar_product(p);

    if (v < 0 || v > 1) {
        return false;
    } 

    double t = tmp * e2.scalar_product(q);

    Vector intersection = Vector(segment.get_start_point()) + t * segment.get_direction_vector();
    
    return segment.is_point_belong(Point(intersection.get_x(),
                                         intersection.get_y(),
                                         intersection.get_z()));
}

bool Geometry::Triangle::is_intersect_for_point(const Triangle& triangle) const {
    if (triangle.is_point()) {
        return a.is_equal(triangle.a);
    }
    else if (triangle.is_segment()) {
        return Segment(triangle.a, triangle.c).is_point_belong(a);
    }
    return triangle.is_point_belong(a);
}

bool Geometry::Triangle::is_intersect_for_segment(const Triangle& triangle) const {
    if (triangle.is_point()) {
        return Segment(a, c).is_point_belong(triangle.a);
    }
    else if (triangle.is_segment()) {
        return !Segment(triangle.a, triangle.c).is_equal(Segment(a, c));
    }
    return triangle.is_intersect_segment(Segment(a, c));
}

bool Geometry::Triangle::is_intersect(const Triangle& triangle) const {
    if (is_point()) {
        return is_intersect_for_point(triangle);
    }
    else if (is_segment()) {
        return is_intersect_for_segment(triangle);
    }
    else {
        if (triangle.is_point()) {
            return is_point_belong(triangle.a);
        }
        else if (triangle.is_segment()) {
            return is_intersect_segment(Segment(triangle.a, triangle.c));
        }
    }
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

            Segment segment1 = intersection_line_in_same_plane(intersection_line);
            Segment segment2 = triangle.intersection_line_in_same_plane(intersection_line);

            Segment intersection = segment1.collinear_segments_intersection(segment2);

            if (!intersection.is_equal(NAN_SEGMENT)) {
                return true;
            }
            return false;
        }
    }
}
