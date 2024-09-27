#include "vector.hpp"
#include "tools.hpp"
#include "iostream"
#include "plane.hpp"
#include <cassert>

Vector Vector::operator+(Vector vector) const {
    return {x + vector.x, y + vector.y, z + vector.z};
}

Vector Vector::operator*(double number) const {
    return {number * x, number * y, number * z};
}

Vector operator*(double number, const Vector& vector) {
    return vector * number;
}

Vector Vector::operator/(double number) const {
    assert(number != 0);

    return Vector::operator*(1/number);
}

Vector operator/(double number, const Vector& vector) {
    return vector/number;
}

int Vector::normalize() {
    double coefficient = vector_module();

    x /= coefficient;
    y /= coefficient;
    z /= coefficient;

    return 0; 
}

bool Vector::is_equal(const Vector& vector) const{
    return (is_equal_doubles(x, vector.x) && 
            is_equal_doubles(y, vector.y) &&
            is_equal_doubles(z, vector.z));
}

Vector Vector::opposite() const {
    return {-x, -y, -z};
}

Vector Vector::vector_product(const Vector& vector) const {
    return {det_two(y, z,  vector.y, vector.z),
            -det_two(x, z,  vector.x, vector.z),
            det_two(x, y,  vector.x, vector.y)};
}

double Vector::triple_product(const Vector& a, const Vector& b) const {
    return x * det_two(a.y, a.z,  b.y, b.z)-
           y * det_two(a.x, a.z,  b.x, b.z)+
           z * det_two(a.x, a.y,  b.x, b.y);
}

double Vector::vector_module() const {
    return (pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 0.5));
}

bool Vector::is_collinear(const Vector& vector) const {
    return (vector_product(vector).vector_module() == 0);   
}

bool Vector::is_skew(const Vector& vector) const {
    return triple_product(vector, {x, y, z}) == 0;
}

double Vector::scalar_product(const Vector& vector) const {
    return x * vector.x + y * vector.y + z * vector.z;
}

Vector Vector::find_perp_in_plane(const Plane& plane) const {
    return vector_product(plane.normal);
}


void Vector::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
