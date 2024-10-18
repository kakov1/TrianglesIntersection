#pragma once

#include "triangle.hpp"
#include "vector.hpp"
#include "point.hpp"
#include "tools.hpp"
#include <array>
#include <list>
#include <iterator>
#include <set>

namespace Octree {

    const double MIN_SIZE = 1;

    using namespace Geometry;
    using triangles_list = std::list<std::pair<Triangle, size_t>>;

    struct CubeParams {
            double x_min;
            double y_min;
            double z_min;
            double x_max;
            double y_max;
            double z_max;
    };

    class Cube {
        private:
            Vector min;
            Vector max;

        public:
            Cube(){};
            Cube(const Vector& point1, const Vector& point2)
            : min(point1), max(point2){};
            Cube(const CubeParams& cube_params)
            : min(cube_params.x_min, cube_params.y_min, cube_params.z_min),
              max(cube_params.x_max, cube_params.y_max, cube_params.z_max){};

            Vector get_min() const {
                return min;
            }

            Vector get_max() const {
                return max;
            }

            void partition(std::array<Cube, 8>& cubes) const {
                Vector center = (min + max) / 2;

                cubes[0] = Cube(min, center);
                cubes[1] = Cube(Vector(center.get_x(), min.get_y(), min.get_z()),
                Vector(max.get_x(), center.get_y(), center.get_z()));
                cubes[2] = Cube(Vector(center.get_x(), min.get_y(), center.get_z()),
                Vector(max.get_x(), center.get_y(), max.get_z()));
                cubes[3] = Cube(Vector(min.get_x(), min.get_y(), center.get_z()),
                Vector(center.get_x(), center.get_y(), max.get_z()));
                cubes[4] = Cube(Vector(min.get_x(), center.get_y(), min.get_z()),
                Vector(center.get_x(), max.get_y(), center.get_z()));
                cubes[5] = Cube(Vector(center.get_x(), center.get_y(), min.get_z()),
                Vector(max.get_x(), max.get_y(), center.get_z()));
                cubes[6] = Cube(center, max);
                cubes[7] = Cube(Vector(min.get_x(), center.get_y(), center.get_z()),
                Vector(center.get_x(), max.get_y(), max.get_z()));
            }

            bool is_point_in_cube(const Point& point) const {
                return point.get_x() > min.get_x() && point.get_x() < max.get_x() &&
                point.get_y() > min.get_y() && point.get_y() < max.get_y() &&
                point.get_z() > min.get_z() && point.get_z() < max.get_z();
            }

            bool is_triangle_in_cube(const Triangle& triangle) const {
                return is_point_in_cube(triangle.get_a()) &&
                is_point_in_cube(triangle.get_b()) &&
                is_point_in_cube(triangle.get_c());
            }

            bool is_part_of_triangle_in_cube(const Triangle& triangle) const {
                return is_point_in_cube(triangle.get_a()) ||
                is_point_in_cube(triangle.get_b()) ||
                is_point_in_cube(triangle.get_c());
            }
    };

    class Node {
        public:
            Cube region_;
            triangles_list triangles_;
            std::array<Node*, 8> children_;
            bool has_child = false;

            Node(const triangles_list& objects, const Cube& region) {
                region_    = region;
                triangles_ = objects;
            }

            ~Node() {
                if (!has_child)
                    return;
                for (Node* child : children_) {
                    delete child;
                }
            }

            Node* create_node(const triangles_list& triangles, const Cube& region) {
                Node* new_node_ptr = new Node(triangles, region);

                return new_node_ptr;
            }

            void build_tree() {
                if (triangles_.size() <= 3)
                    return;

                Vector cube_params = region_.get_max() - region_.get_min();

                if (cube_params.get_x() < MIN_SIZE &&
                cube_params.get_y() < MIN_SIZE && cube_params.get_z() < MIN_SIZE) {
                    return;
                }

                std::array<Cube, 8> cubes;
                region_.partition(cubes);
                std::array<triangles_list, 8> triangles_partition;
                std::list<triangles_list::iterator> triangles_deletion;

                for (auto triangle_it = triangles_.begin();
                     triangle_it != triangles_.end(); triangle_it++) {
                    for (int part_num = 0; part_num < 8; part_num++) {
                        if (!cubes[part_num].is_triangle_in_cube(triangle_it->first))
                            continue;
                        triangles_partition[part_num].push_back(*triangle_it);
                        triangles_deletion.push_back(triangle_it);
                        break;
                    }
                }

                for (auto triangle_ptr : triangles_deletion) {
                    triangles_.erase(triangle_ptr);
                }

                for (int child_num = 0; child_num < 8; child_num++) {
                    if (!triangles_partition[child_num].empty()) {
                        has_child = true;
                        children_[child_num] =
                        create_node(triangles_partition[child_num], cubes[child_num]);
                        children_[child_num]->build_tree();
                    }
                    else {
                        children_[child_num] = nullptr;
                    }
                }
            }

            void get_intersections_in_cube(std::set<size_t>& result) const {
                if (triangles_.empty())
                    return;
                triangles_list triangles_copy = triangles_;

                for (auto triangle1 : triangles_) {
                    for (auto triangle2 : triangles_copy) {
                        if (triangle1.second == triangle2.second ||
                        !triangle1.first.is_intersect(triangle2.first))
                            continue;
                        result.insert(triangle1.second);
                        result.insert(triangle2.second);
                    }
                    if (!triangles_copy.empty()) {
                        triangles_copy.pop_front();
                    }
                }
            }

            void get_intersections_with_child(std::set<size_t>& result,
            const triangles_list& triangles,
            const Node* child) const {
                if (child == nullptr || child->triangles_.empty())
                    return;

                for (auto triangle1 : triangles) {
                    for (auto triangle2 : child->triangles_) {
                        if (!child->region_.is_part_of_triangle_in_cube(
                            triangle1.first) ||
                        !triangle1.first.is_intersect(triangle2.first))
                            continue;
                        result.insert(triangle1.second);
                        result.insert(triangle2.second);
                    }
                }
            }

            void get_intersections_with_children(std::set<size_t>& result,
            const triangles_list& triangles) const {
                if (!has_child)
                    return;
                for (Node* child : children_) {
                    if (child == nullptr)
                        continue;

                    get_intersections_with_child(result, triangles, child);
                    child->get_intersections_with_children(result, triangles);
                }
            }

            std::set<size_t> get_intersections() const {
                if ((triangles_.empty()) && !has_child) {
                    return {};
                }

                std::set<size_t> result;

                get_intersections_with_children(result, triangles_);
                get_intersections_in_cube(result);

                if (!has_child)
                    return result;
                for (Node* child : children_) {
                    if (child == nullptr)
                        continue;
                    std::set<size_t> result_child = child->get_intersections();
                    for (size_t triangle_num : result_child) {
                        result.insert(triangle_num);
                    }
                }

                return result;
            }
    };

    class Octree {
        private:
            Node* root;

        public:
            Octree(const triangles_list& objects, const CubeParams& cube_params) {
                root = root->create_node(objects, Cube(cube_params));
                root->build_tree();
            }

            ~Octree() {
                delete root;
            }

            std::set<size_t> get_intersections() const {
                return root->get_intersections();
            }
    };
}