#include "octree.hpp"
#include <iostream>
#include <iterator>
#include <set>

Octree::Cube::Cube() {};
Octree::Cube::Cube(const Vector& point1, const Vector& point2) : min(point1), max(point2) {};

Geometry::Vector Octree::Cube::get_min() const { return min; }
Geometry::Vector Octree::Cube::get_max() const { return max; }

void Octree::Cube::partition(Cube cubes[8]) const {
    Vector center = (min + max)/2;

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

bool Octree::Cube::is_point_in_cube(const Point& point) const {
    return (point.get_x() > min.get_x() || is_equal_doubles(point.get_x(), min.get_x())) &&
           (point.get_x() < max.get_x() || is_equal_doubles(point.get_x(), max.get_x())) &&
           (point.get_y() > min.get_y() || is_equal_doubles(point.get_y(), min.get_y())) &&
           (point.get_y() < max.get_y() || is_equal_doubles(point.get_y(), max.get_y())) &&
           (point.get_z() > min.get_z() || is_equal_doubles(point.get_z(), min.get_z())) &&
           (point.get_z() < max.get_z() || is_equal_doubles(point.get_z(), max.get_z()));
}  

bool Octree::Cube::is_triangle_in_cube(const Triangle& triangle) const {
    return is_point_in_cube(triangle.get_a()) &&
           is_point_in_cube(triangle.get_b()) &&
           is_point_in_cube(triangle.get_c());
}

bool Octree::Cube::is_part_of_triangle_in_cube(const Triangle& triangle) const {
    return is_point_in_cube(triangle.get_a()) ||
           is_point_in_cube(triangle.get_b()) ||
           is_point_in_cube(triangle.get_c());
}

Octree::Node::Node(const triangles_list& objects, const Cube& region) {
    region_ = region;
    triangles_ = objects;
}

Octree::Node::~Node() {
    if (has_child) {
        for (Node* child : childs_) {
            delete child;
        }
    }
}

Octree::Node* Octree::Node::create_node(const triangles_list& triangles, const Cube& region) {
    Node* new_node_ptr = new Node(triangles, region);

    return new_node_ptr;
}

void Octree::Node::build_tree() {
    if (triangles_.size() <= 10) {
        return;
    }

    Vector cube_params = region_.get_max() - region_.get_min();

    if (cube_params.get_x() < MIN_SIZE && cube_params.get_y() < MIN_SIZE && cube_params.get_z() < MIN_SIZE) {
        return;
    }
    
    Cube cubes[8];
    region_.partition(cubes);
    triangles_list triangles_partition[8];
    std::list<triangles_list::iterator> triangles_deletion;

    for (auto triangle_it = triangles_.begin(); triangle_it != triangles_.end(); triangle_it++) {
        for (int part_num = 0; part_num < 8; part_num++) {
            if (cubes[part_num].is_triangle_in_cube(triangle_it->first)) {
                triangles_partition[part_num].push_back(*triangle_it);
                triangles_deletion.push_back(triangle_it);
                break;
            }         
        }
    }
    
    for (auto triangle_ptr : triangles_deletion) {
        triangles_.erase(triangle_ptr);
    }

    for (int child_num = 0; child_num < 8; child_num++) {
        if (!triangles_partition[child_num].empty()) {
            has_child = true;
            childs_[child_num] = create_node(triangles_partition[child_num], cubes[child_num]);
            childs_[child_num]->build_tree();
        }
        else {
            childs_[child_num] = nullptr;
        }
    }
}

void Octree::Node::get_intersections_between_cubes(std::set<size_t>& result,
                                                   const triangles_list& triangles) const {
    if (!triangles_.empty() && !triangles.empty()) {
        triangles_list triangles_copy = triangles;

        for (auto triangle1 : triangles_) {
            for (auto triangle2 : triangles_copy) {
                if (triangle1.second != triangle2.second &&
                    region_.is_part_of_triangle_in_cube(triangle2.first)) {
                    if (triangle1.first.is_intersect(triangle2.first)) {
                        result.insert(triangle1.second);
                        result.insert(triangle2.second);
                    }
                }
            }
            if (triangles_copy.size() != 0) {
                triangles_copy.pop_front();
            }
        }
    }
}

void Octree::Node::get_intersections_with_children(std::set<size_t>& result,
                                                   const triangles_list& triangles) const {
    if (has_child) {
        for (Node* child : childs_) {
            if (child != nullptr) {
                child->get_intersections_between_cubes(result, triangles);
                child->get_intersections_with_children(result, triangles);
            }
        }
    }
}

std::set<size_t> Octree::Node::get_intersections() const {
    if ((triangles_.empty()) && !has_child) {
        return {};
    }

    std::set<size_t> result;

    get_intersections_with_children(result, triangles_);
    get_intersections_between_cubes(result, triangles_);

    if (has_child) {
        for (Node* child : childs_) {
            if (child != nullptr) {
                std::set<size_t> result_child = child->get_intersections();
                for (size_t triangle_num : result_child) {
                    result.insert(triangle_num);
                }
            }
        }
    }

    return result;
}

Octree::Octree::Octree(const triangles_list& objects, const Cube& region) {
    root = root->create_node(objects, region);
    root->build_tree();
}

Octree::Octree::~Octree() {
    delete root;
}

std::set<size_t> Octree::Octree::get_intersections() const {
    return root->get_intersections();
}
