#include <iostream>
#include <utility>
#include <cmath>
#include <fstream>
#include "plane.hpp"
#include <vector>

int main() {
    Plane plane = Plane({10, 15, 20}, 3);
    Vector vector = Vector(-6, 9, 2);

    vector.find_perp_in_plane(plane).print();

    return 0;
}