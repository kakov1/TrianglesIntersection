#pragma once

#include "point.hpp"

namespace Geometry {
    class Vector {
        private:
            double x = NAN;
            double y = NAN;
            double z = NAN;
        public:
            Vector() {}
            Vector(double coord_x, double coord_y, double coord_z);
            Vector(const Point& point1, const Point& point2);
            Vector(const Point& point);

            double get_x() const;
            double get_y() const;
            double get_z() const;

            void print() const;
            bool is_equal(const Vector& vector) const;
            bool is_collinear(const Vector& vector) const;
            bool is_skew(const Vector& vector) const;
            bool is_codirectional(const Vector& vector) const;
            double scalar_product(const Vector& vector) const;
            double triple_product(const Vector& a, const Vector& b) const;
            double vector_module() const;
            double length() const;
            Vector vector_product(const Vector& vector) const;
            Vector operator+(const Vector& vector) const;
            Vector operator-(const Vector& vector) const;
            Vector operator*(double number) const;
            Vector operator/(double number) const;
            Vector opposite() const;
    };

    Vector operator*(double number, const Vector& vector);
    Vector operator/(double number, const Vector& vector);
}