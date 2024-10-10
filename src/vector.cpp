#include "vector.hpp"
#include "tools.hpp"
#include <iostream>

double Geometry::Vector::get_x() const {
    return x;
}
double Geometry::Vector::get_y() const {
    return y;
}
double Geometry::Vector::get_z() const {
    return z;
}

Geometry::Vector::Vector(double coord_x, double coord_y, double coord_z) {
    x = coord_x;
    y = coord_y;
    z = coord_z;
}

Geometry::Vector::Vector(const Point& point1, const Point& point2) {
    x = point2.get_x() - point1.get_x();
    y = point2.get_y() - point1.get_y();
    z = point2.get_z() - point1.get_z();
}

Geometry::Vector::Vector(const Point& point) {
    x = point.get_x();
    y = point.get_y();
    z = point.get_z();
}

Geometry::Vector Geometry::Vector::operator+(const Vector& vector) const {
    return {x + vector.x, y + vector.y, z + vector.z};
}

Geometry::Vector Geometry::Vector::operator-(const Vector& vector) const {
    return {x - vector.x, y - vector.y, z - vector.z};
}

Geometry::Vector Geometry::Vector::operator*(double number) const {
    return {number * x, number * y, number * z};
}

Geometry::Vector Geometry::operator*(double number, const Vector& vector) {
    return vector * number;
}

Geometry::Vector Geometry::Vector::operator/(double number) const {
    return Geometry::Vector::operator*(1/number);
}

Geometry::Vector Geometry::operator/(double number, const Vector& vector) {
    return vector/number;
}

bool Geometry::Vector::is_equal(const Vector& vector) const{
    return (is_equal_doubles(x, vector.x) && 
            is_equal_doubles(y, vector.y) &&
            is_equal_doubles(z, vector.z));
}

Geometry::Vector Geometry::Vector::opposite() const {
    return {-x, -y, -z};
}

Geometry::Vector Geometry::Vector::vector_product(const Vector& vector) const {
    return {det_two(y, z,  vector.y, vector.z),
            -det_two(x, z,  vector.x, vector.z),
            det_two(x, y,  vector.x, vector.y)};
}

double Geometry::Vector::length() const {
    return pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 0.5);
}

bool Geometry::Vector::is_codirectional(const Vector& vector) const {
    if (!is_collinear(vector)) {
        return false;
    }
    return is_equal_doubles(length()*vector.length(), scalar_product(vector));
}

double Geometry::Vector::triple_product(const Vector& a, const Vector& b) const {
    return x * det_two(a.y, a.z,  b.y, b.z)-
           y * det_two(a.x, a.z,  b.x, b.z)+
           z * det_two(a.x, a.y,  b.x, b.y);
}

double Geometry::Vector::vector_module() const {
    return (pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 0.5));
}

bool Geometry::Vector::is_collinear(const Vector& vector) const {
    return (vector_product(vector).vector_module() == 0);   
}

bool Geometry::Vector::is_skew(const Vector& vector) const {
    return triple_product(vector, {x, y, z}) == 0;
}

double Geometry::Vector::scalar_product(const Vector& vector) const {
    return x * vector.x + y * vector.y + z * vector.z;
}

void Geometry::Vector::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
