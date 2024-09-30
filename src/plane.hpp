#pragma once

#include "tools.hpp"
#include "line.hpp"
#include "vector.hpp"

class Vector;

class Plane {
    public:
        Vector normal;
        double d;

        Plane() {};
        Plane(const Vector& normal_vector, const double coeff_d) {
            normal = normal_vector;
            d = coeff_d;
        }
        Plane(const Point& point1, const Point& point2, const Point& point3) {
            if (point1.is_equal(NAN_POINT) && point2.is_equal(NAN_POINT) && point3.is_equal(NAN_POINT)) {
                normal = NAN_VECTOR;
                d = NAN;
                return;
            }
            normal.x = det_two(point2.y - point1.y, point2.z - point1.z,
                               point3.y - point1.y, point3.z - point1.z);
            normal.y = -det_two(point2.x - point1.x, point2.z - point1.z,
                                point3.x - point1.x, point3.z - point1.z); 
            normal.z = det_two(point2.x - point1.x, point2.y - point1.y,
                               point3.x - point1.x, point3.y - point1.y);
            d = -(point1.x*normal.x)-(point1.y*normal.y)-(point1.z*normal.z);
            //normalize();
        }

        bool is_equal(const Plane& plane) const;
        bool is_collinear(const Plane& plane) const;
        Line intersection(const Plane& plane) const;
        bool is_point_over_plane(const Point& point) const;
        bool is_point_under_plane(const Point& point) const;
        bool is_point_belong(const Point& point) const;
        void print() const;
        int normalize();
};