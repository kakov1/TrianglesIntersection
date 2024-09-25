#include "plane.hpp"
#include "tools.hpp"
#include "line.hpp"
#include <iostream>

int main() {
    Point point1(1, 2, 3);
    Point point2(2, 1, 0);
    Point point3(1, 0, 2);
    Point point4(2, 3, 0);
    Line line1(point1, point2);
    Line line2(point3, point4);

    line1.start_point.print();
    line1.direction_vector.print();
    line2.start_point.print();
    line2.direction_vector.print();

    Point a = line1.lines_intersection(line2);
    a.print();

    return 0;
}