#pragma once

#include "point.hpp"
#include <cmath>

class Vector {
    public:
        float x = NAN;
        float y = NAN;
        float z = NAN;

        Vector() {}
        Vector(float coord_x, float coord_y, float coord_z) {
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
        float scalar_product(const Vector& vector) const;
        Vector vector_product(const Vector& vector) const;
        float triple_product(const Vector& a, const Vector& b) const;
        float vector_module() const;
        bool is_collinear(const Vector& vector) const;
        bool is_skew(const Vector& vector) const;
        Vector operator+(Vector vector) const;
        Vector operator*(float number) const;
        Vector operator/(float number) const;
};

Vector operator*(float number, const Vector& vector);
Vector operator/(float number, const Vector& vector);