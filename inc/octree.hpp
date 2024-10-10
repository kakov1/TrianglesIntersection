#pragma once

#include "triangle.hpp"
#include "vector.hpp"
#include "point.hpp"
#include "tools.hpp"
#include <list>
#include <iterator>
#include <set>

namespace Octree {

    const double MIN_SIZE = 1;

    using namespace Geometry;
    using triangles_list = std::list<std::pair<Triangle, size_t>>;

    class Cube {
        private:
            Vector min;
            Vector max;
        public:
            Cube();
            Cube(const Vector& point_min, const Vector& point_max);

            Vector get_min() const;
            Vector get_max() const;

            void partition(Cube cubes[8]) const;
            bool is_point_in_cube(const Point& point) const;
            bool is_triangle_in_cube(const Triangle& triangle) const;
            bool is_part_of_triangle_in_cube(const Triangle& triangle) const;
            bool is_triangle_intersect_edge(const Triangle& triangle) const;
    };

    class Node {
        public:
            Cube region_;
            triangles_list triangles_;
            Node* children_[8];
            bool has_child = false;

            Node(const triangles_list& objects, const Cube& region);
            ~Node();

            void build_tree();
            Node* create_node(const triangles_list& triangles, const Cube& region);
            void get_intersections_in_cube(std::set<size_t>& result) const;
            void get_intersections_with_children(std::set<size_t>& result,
                                                 const triangles_list& parent_triangles) const;
            std::set<size_t> get_intersections() const;
    };

    class Octree {
        private:
            Node* root;
        public:
            Octree(const triangles_list& objects, const Cube& region);
            ~Octree();
            std::set<size_t> get_intersections() const;
    };
}