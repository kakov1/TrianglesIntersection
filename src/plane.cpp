#include "plane.hpp"
#include "tools.hpp"
#include <iostream>
#include <cmath>

Vector Plane::get_normal() const { return normal; }

double Plane::get_d() const { return d; }

Plane::Plane(const Vector& normal_vector, const double coeff_d) {
    normal = normal_vector;
    d = coeff_d;
}

Plane::Plane(const Point& point1, const Point& point2, const Point& point3) {
    if (point1.is_equal(NAN_POINT) && point2.is_equal(NAN_POINT) && point3.is_equal(NAN_POINT)) {
        normal = NAN_VECTOR;
        d = NAN;
        return;
    }
    double normal_x = det_two(point2.get_y() - point1.get_y(), point2.get_z() - point1.get_z(),
                              point3.get_y() - point1.get_y(), point3.get_z() - point1.get_z());
    double normal_y = -det_two(point2.get_x() - point1.get_x(), point2.get_z() - point1.get_z(),
                               point3.get_x() - point1.get_x(), point3.get_z() - point1.get_z()); 
    double normal_z = det_two(point2.get_x() - point1.get_x(), point2.get_y() - point1.get_y(),
                              point3.get_x() - point1.get_x(), point3.get_y() - point1.get_y());
    d = -(point1.get_x()*normal_x)-(point1.get_y()*normal_y)-(point1.get_z()*normal_z);

    normal = Vector(normal_x, normal_y, normal_z);
}

Vector Plane::find_perp_in_plane(const Vector& vector) const {
    return vector.vector_product(get_normal());
}

bool Plane::is_equal(const Plane& plane) const {
    if (is_collinear(plane)) {
        return is_equal_doubles(d, plane.d);
    }
    return false;
}

bool Plane::is_point_belong(const Point& point) const {
    return is_equal_doubles(normal.get_x() * point.get_x() +
                            normal.get_y() * point.get_y() +
                            normal.get_z() * point.get_z() + d, 0);
}

bool Plane::is_collinear(const Plane& plane) const {
    return normal.is_collinear(plane.normal);
}

int Plane::normalize() {
    double coefficient = d;

    normal.normalize();
    d /= coefficient;

    if (d < 0) d *= (-1);

    return 0;
}

void Plane::print() const {
    std::cout << normal.get_x() << "x" << sign(normal.get_y()) <<
                 fabs(normal.get_y()) << "y" << sign(normal.get_z()) <<
                 fabs(normal.get_z()) << "z" << sign(d) << fabs(d) << "=0" << std::endl;
}

bool Plane::is_point_over_plane(const Point& point) const {
    double result = normal.get_x() * point.get_x() +
                    normal.get_y() * point.get_y() +
                    normal.get_z() * point.get_z() + d;
    return (result > 0 && !is_equal_doubles(result, 0));
}

bool Plane::is_point_under_plane(const Point& point) const {
    double result = normal.get_x() * point.get_x() +
                    normal.get_y() * point.get_y() +
                    normal.get_z() * point.get_z() + d;
    return (result < 0 && !is_equal_doubles(result, 0));
}

Line Plane::intersection(const Plane& plane) const {
    Vector n = normal.vector_product(plane.normal); 

    if (n.vector_module() == 0) {
        return {NAN_POINT, NAN_VECTOR};
    } 

    double a, b;

    double normals_scalar_product = normal.scalar_product(plane.normal);
    double normal1_length_sqr = normal.scalar_product(normal);
    double normal2_length_sqr = plane.normal.scalar_product(plane.normal);

    a = (d * normal2_length_sqr - plane.d * normals_scalar_product) /
        (pow(normals_scalar_product, 2) - normal1_length_sqr*normal2_length_sqr);
    b = (plane.d * normal1_length_sqr - d * normals_scalar_product) /
        (pow(normals_scalar_product, 2) - normal1_length_sqr*normal2_length_sqr);

    Vector start_vector = a * normal + b * plane.normal;
    Line result = Line(Point(start_vector.get_x(), start_vector.get_y(),
                             start_vector.get_z()), n);

    return result;
}