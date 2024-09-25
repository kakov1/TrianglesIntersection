#include "segment.hpp"
#include "tools.hpp"
#include "point.hpp"
#include <cmath>
#include <cassert>
#include <algorithm>

bool Segment::is_on_same_line(const Segment& segment) const {
    assert(is_valid());

    if (direction_vector.is_collinear(segment.direction_vector)) {
        Vector connection_origins = {start_point.x - segment.start_point.x,
                                     start_point.y - segment.start_point.y,
                                     start_point.z - segment.start_point.z};
        connection_origins.normalize();

        return (direction_vector.is_equal(connection_origins) ||
                direction_vector.is_equal(connection_origins.opposite()));
    }

    return false;
}

bool Segment::is_intersect(const Segment& segment) const {
    assert(is_valid());

    if (!direction_vector.is_collinear(segment.direction_vector)) {
        float main_det = det_two(direction_vector.x, -segment.direction_vector.x,
                                 direction_vector.y, -segment.direction_vector.y);
    }
    return false;
}

bool Segment::is_point_belong(const Point& point) const {
    return pow(det_two(point.x - start_point.x, point.y - start_point.y,
               direction_vector.x, direction_vector.y), 2) +
           pow(det_two(point.y - start_point.y, point.z - start_point.z,
               direction_vector.y, direction_vector.z), 2) +
           pow(det_two(point.x - start_point.x, point.z - start_point.z,
               direction_vector.x, direction_vector.z), 2) == 0 &&
           std::min(start_point.x, end_point.x) < point.x < std::max(start_point.x, end_point.x) &&
           std::min(start_point.y, end_point.y) < point.y < std::max(start_point.y, end_point.y) &&
           std::min(start_point.z, end_point.z) < point.z < std::max(start_point.z, end_point.z);
}

bool Segment::is_valid() const {
    return (start_point.is_valid() && end_point.is_valid() && !start_point.is_equal(end_point));
}