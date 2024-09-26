#include "plane.hpp"
#include "vector.hpp"
#include "line.hpp"
#include <iostream>
#include <cmath>

bool Plane::is_equal(const Plane& plane) const {
    if (is_collinear(plane)) {
        return is_equal_floats(d, plane.d);
    }
    return false;
}

bool Plane::is_collinear(const Plane& plane) const {
    return normal.is_collinear(plane.normal);
}

int Plane::normalize() {
    float coefficient = pow(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2), 0.5);

    normal.x /= coefficient;
    normal.y /= coefficient;
    normal.z /= coefficient;
    d /= coefficient;

    if (d < 0) d *= (-1);

    return 0;
}

void Plane::print() const {
    std::cout << normal.x << "x" << sign(normal.y) << fabs(normal.z) << "y" << sign(normal.z)
              << fabs(normal.z) << "z" << sign(d) << fabs(d) << "=0" << std::endl;
}

bool Plane::is_point_over_plane(const Point& point) const {
    return normal.x * point.x + normal.y * point.y + normal.z * point.z + d > 0;
}

Line Plane::intersection(const Plane& plane) const {
    Line result;

    Vector n = normal.vector_product(plane.normal); 

    if (n.vector_module() == 0) {
        return {NAN_POINT, NAN_VECTOR};
    } 

    result.direction_vector = n;
    float a, b;

    float normals_scalar_product = normal.scalar_product(plane.normal);
    float normal1_length_sqr = normal.scalar_product(normal);
    float normal2_length_sqr = plane.normal.scalar_product(plane.normal);

    a = (d * normal2_length_sqr - plane.d * normals_scalar_product) /
        (pow(normals_scalar_product, 2) - normal1_length_sqr*normal2_length_sqr);
    b = (plane.d * normal1_length_sqr - d * normals_scalar_product) /
        (pow(normals_scalar_product, 2) - normal1_length_sqr*normal2_length_sqr);

    Vector start_vector = a * normal + b * plane.normal;
    result.start_point = {start_vector.x, start_vector.y, start_vector.z};

    return result;
}