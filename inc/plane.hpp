#pragma once

#include "vector.hpp"
#include "line.hpp"
#include "point.hpp"

class Vector;

class Plane {
    private:
        Vector normal;
        double d;
    public:
        Plane() {};
        Plane(const Vector& normal_vector, const double coeff_d);
        Plane(const Point& point1, const Point& point2, const Point& point3);
        
        Vector get_normal() const;
        double get_d() const;

        bool is_equal(const Plane& plane) const;
        bool is_collinear(const Plane& plane) const;
        Line intersection(const Plane& plane) const;
        bool is_point_over_plane(const Point& point) const;
        bool is_point_under_plane(const Point& point) const;
        bool is_point_belong(const Point& point) const;
        void print() const;
        Vector find_perp_in_plane(const Vector& vector) const;
        Plane normalize() const;
};