#include "plane.hpp"
#include "tools.hpp"
#include "line.hpp"
#include "triangle.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <set>

int main() {
    size_t triangles_number;
    std::cin >> triangles_number;
    std::vector<Triangle> triangles;

    for (int i = 0; i < triangles_number; i++) {
        double x, y, z;
        std::vector<Point> triangle_points;
        for (int j = 0; j < 3; j++) {
            std::cin >> x >> y >> z;
            triangle_points.push_back(Point(x, y, z));
        }
        triangles.emplace_back(triangle_points[0], triangle_points[1], triangle_points[2]);
    }



    for (int i = 0; i < triangles_number; i++) {
        for (int j = 0; j < triangles_number; j++) {
            if (i != j && triangles[i].is_intersect(triangles[j])) {
                std::cout << i << std::endl;
                break;
            }
        }
    }

    return 0;
}