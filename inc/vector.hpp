#pragma once

#include "point.hpp"
#include "tools.hpp"
#include <cmath>
#include <iostream>

namespace Geometry {
    template <typename FloatType>
    class Vector {
        private:
            FloatType x = NAN;
            FloatType y = NAN;
            FloatType z = NAN;

        public:
            Vector() = default;

            Vector(FloatType coord_x, FloatType coord_y, FloatType coord_z) {
                x = coord_x;
                y = coord_y;
                z = coord_z;
            }

            Vector(const Point<FloatType>& point1,
                   const Point<FloatType>& point2) {
                x = point2.get_x() - point1.get_x();
                y = point2.get_y() - point1.get_y();
                z = point2.get_z() - point1.get_z();
            }

            Vector(const Point<FloatType>& point) {
                x = point.get_x();
                y = point.get_y();
                z = point.get_z();
            }

            const FloatType& get_x() const { return x; }

            const FloatType& get_y() const { return y; }

            const FloatType& get_z() const { return z; }

            Vector operator+(const Vector& vector) const {
                return {x + vector.x, y + vector.y, z + vector.z};
            }

            Vector operator-(const Vector& vector) const {
                return {x - vector.x, y - vector.y, z - vector.z};
            }

            Vector operator*(FloatType number) const {
                return {number * x, number * y, number * z};
            }

            Vector operator/(FloatType number) const {
                return operator*(1 / number);
            }

            bool is_equal(const Vector& vector) const {
                return (is_equal_floats(x, vector.x) &&
                        is_equal_floats(y, vector.y) &&
                        is_equal_floats(z, vector.z));
            }

            Vector opposite() const { return {-x, -y, -z}; }

            Vector vector_product(const Vector& vector) const {
                return {det_two(y, z, vector.y, vector.z),
                        -det_two(x, z, vector.x, vector.z),
                        det_two(x, y, vector.x, vector.y)};
            }

            FloatType length() const {
                return std::pow(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2), 0.5);
            }

            bool is_codirectional(const Vector& vector) const {
                if (!is_collinear(vector)) {
                    return false;
                }
                return is_equal_floats(length() * vector.length(),
                                       scalar_product(vector));
            }

            FloatType triple_product(const Vector& a, const Vector& b) const {
                return x * det_two(a.y, a.z, b.y, b.z) -
                       y * det_two(a.x, a.z, b.x, b.z) +
                       z * det_two(a.x, a.y, b.x, b.y);
            }

            FloatType vector_module() const {
                return (std::pow(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2), 0.5));
            }

            bool is_collinear(const Vector& vector) const {
                return (is_zero(vector_product(vector).vector_module()));
            }

            bool is_skew(const Vector& vector) const {
                return is_zero(triple_product(vector, {x, y, z}));
            }

            FloatType scalar_product(const Vector& vector) const {
                return x * vector.x + y * vector.y + z * vector.z;
            }

            void print() const {
                std::cout << "(" << x << ", " << y << ", " << z << ")"
                          << std::endl;
            }
    };

    template <typename FloatType>
    Vector<FloatType> operator*(FloatType number,
                                const Vector<FloatType>& vector) {
        return vector * number;
    }

    template <typename FloatType>
    Vector<FloatType> operator/(FloatType number,
                                const Vector<FloatType>& vector) {
        return vector / number;
    }
} // namespace Geometry