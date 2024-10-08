#include "triangle.hpp"
#include "octree.hpp"
#include <list>
#include <iostream>

int main() {
    size_t triangles_number;
    std::cin >> triangles_number;
    std::list<std::pair<Geometry::Triangle, size_t>> triangles;

    double x_min, y_min, z_min, x_max, y_max, z_max;

    for (int i = 0; i < triangles_number; i++) {
        double x, y, z;
        Geometry::Point triangle_points[3];
        for (int j = 0; j < 3; j++) {
            std::cin >> x >> y >> z;
            triangle_points[j] = Geometry::Point(x, y, z);
            if (i == 0) {
                x_min = x;
                y_min = y;
                z_min = z;
                x_max = x;
                y_max = y;
                z_max = z;
                continue;
            }
            x_min = x<x_min?x:x_min;
            y_min = y<y_min?y:y_min;
            z_min = z<z_min?z:z_min;
            x_max = x>x_max?x:x_max;
            y_max = y>y_max?y:y_max;
            z_max = z>z_max?z:z_max;
        }
        std::pair<Geometry::Triangle, size_t> triangle = std::pair<Geometry::Triangle, size_t>(Geometry::Triangle(triangle_points[0], triangle_points[1], triangle_points[2]), i);
        triangles.push_back(triangle);
    }

    Octree::Octree tree = Octree::Octree(triangles, Octree::Cube(Geometry::Point(x_min, y_min, z_min),
                                                                 Geometry::Point(x_max, y_max, z_max)));                                                            

    std::set<size_t> res = tree.get_intersections();

    if (res.size() != 0) {
        for (auto i : res) {
            std::cout << i << std::endl;
        }
    }

    return 0;
}