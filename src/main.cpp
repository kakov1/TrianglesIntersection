#include "plane.hpp"
#include "tools.hpp"
#include "line.hpp"
#include "triangle.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

int main() {
    size_t triangles_number;
    std::cin >> triangles_number;
    std::vector<Triangle> triangles;


    for (int i = 0; i < triangles_number; i++) {
        float x1, y1, z1, x2, y2, z2, x3, y3, z3;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
        Point point1(x1, y1, z1);
        Point point2(x2, y2, z2);
        Point point3(x3, y3, z3);
        triangles.emplace_back(point1, point2, point3);
    }



    for (int i = 0; i < triangles_number; i++) {
        for (int j = 0; j < triangles_number; j++) {
            if (i != j && triangles[i].is_intersect(triangles[j])) {
                std::cout << i << std::endl;
            }
        }
    }

    return 0;
}