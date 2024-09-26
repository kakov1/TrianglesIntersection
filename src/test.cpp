#include "line.hpp"
#include <iostream>
#include <utility>
#include <cmath>

int main() {

    Line line1 = {Point(2, 1, 0), Point(2, -3, 1)};
    Line line2 = {Point(2, 2, 0), Point(2, 1, 1)};

    Point inter = line1.lines_intersection(line2);
    
    inter.print();

    return 0;
}