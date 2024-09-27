#pragma once

#include "point.hpp"
#include <cmath>

class Plane;

class Vector {
    public:
        double x = NAN;
        double y = NAN;
        double z = NAN;

        Vector() {}
        Vector(double coord_x, double coord_y, double coord_z) {
            x = coord_x;
            y = coord_y;
            z = coord_z;
        }
        Vector(Point point1, Point point2) {
            x = point2.x - point1.x;
            y = point2.y - point1.y;
            z = point2.z - point1.z;
        }

        void print() const;
        bool is_equal(const Vector& vector) const;
        Vector opposite() const;
        int normalize();
        double scalar_product(const Vector& vector) const;
        Vector vector_product(const Vector& vector) const;
        double triple_product(const Vector& a, const Vector& b) const;
        double vector_module() const;
        bool is_collinear(const Vector& vector) const;
        bool is_skew(const Vector& vector) const;
        Vector find_perp_in_plane(const Plane& plane) const;
        Vector operator+(Vector vector) const;
        Vector operator*(double number) const;
        Vector operator/(double number) const;
};

Vector operator*(double number, const Vector& vector);
Vector operator/(double number, const Vector& vector);