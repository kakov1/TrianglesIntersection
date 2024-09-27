#include <iostream>
#include <utility>
#include <cmath>
#include <fstream>
#include "plane.hpp"
#include <vector>

int main() {
    Plane plane1 = Plane({10, 15, 20}, 3);
    Plane plane2 = Plane({10, 15, 16}, 3);

    plane1.intersection(plane2).print();

    return 0;
}