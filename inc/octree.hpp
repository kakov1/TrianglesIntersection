#pragma once

#include "point.hpp"
#include "tools.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include <array>
#include <iterator>
#include <deque>
#include <list>
#include <set>

namespace Octree {

	using namespace Geometry;

	template <typename FloatType>
	struct CubeParams {
		FloatType x_min;
		FloatType y_min;
		FloatType z_min;
		FloatType x_max;
		FloatType y_max;
		FloatType z_max;
	};

	template <typename FloatType>
	class Cube {
		private:

		Vector<FloatType> min;
		Vector<FloatType> max;

		public:

		Cube() = default;
		Cube(const Vector<FloatType>& point1, const Vector<FloatType>& point2)
			: min(point1), max(point2){};
		Cube(const CubeParams<FloatType>& cube_params)
			: min(cube_params.x_min, cube_params.y_min, cube_params.z_min),
			  max(cube_params.x_max, cube_params.y_max, cube_params.z_max){};

		const Vector<FloatType>& get_min() const { return min; }

		const Vector<FloatType>& get_max() const { return max; }

		void partition(std::array<Cube, 8>& cubes) const {
			Vector<FloatType> center = (min + max) / 2;

			cubes[0] = Cube(min, center);
			cubes[1] = Cube(
				Vector<FloatType>(center.get_x(), min.get_y(), min.get_z()),
				Vector<FloatType>(max.get_x(), center.get_y(), center.get_z()));
			cubes[2] = Cube(
				Vector<FloatType>(center.get_x(), min.get_y(), center.get_z()),
				Vector<FloatType>(max.get_x(), center.get_y(), max.get_z()));
			cubes[3] = Cube(
				Vector<FloatType>(min.get_x(), min.get_y(), center.get_z()),
				Vector<FloatType>(center.get_x(), center.get_y(), max.get_z()));
			cubes[4] = Cube(
				Vector<FloatType>(min.get_x(), center.get_y(), min.get_z()),
				Vector<FloatType>(center.get_x(), max.get_y(), center.get_z()));
			cubes[5] = Cube(
				Vector<FloatType>(center.get_x(), center.get_y(), min.get_z()),
				Vector<FloatType>(max.get_x(), max.get_y(), center.get_z()));
			cubes[6] = Cube(center, max);
			cubes[7] = Cube(
				Vector<FloatType>(min.get_x(), center.get_y(), center.get_z()),
				Vector<FloatType>(center.get_x(), max.get_y(), max.get_z()));
		}

		bool is_point_in_cube(const Point<FloatType>& point) const {
			return is_bigger(point.get_x(), min.get_x()) &&
				   is_less(point.get_x(), max.get_x()) &&
				   is_bigger(point.get_y(), min.get_y()) &&
				   is_less(point.get_y(), max.get_y()) &&
				   is_bigger(point.get_z(), min.get_z()) &&
				   is_less(point.get_z(), max.get_z());
		}

		bool is_triangle_in_cube(const Triangle<FloatType>& triangle) const {
			return is_point_in_cube(triangle.get_a()) &&
				   is_point_in_cube(triangle.get_b()) &&
				   is_point_in_cube(triangle.get_c());
		}

		bool
		is_part_of_triangle_in_cube(const Triangle<FloatType>& triangle) const {
			return is_point_in_cube(triangle.get_a()) ||
				   is_point_in_cube(triangle.get_b()) ||
				   is_point_in_cube(triangle.get_c());
		}
	};

	template <typename FloatType>
	class Octree {
		public:

		using triangles_list =
			std::list<std::pair<Triangle<FloatType>, size_t>>;

		private:

		class Node {
			private:

			const FloatType MIN_SIZE = 1;

			Cube<FloatType> region_;
			triangles_list triangles_;
			std::array<Node*, 8> children_;
			bool has_child = false;

			void build_tree() {
				if (triangles_.size() <= 3)
					return;

				Vector<FloatType> cube_params =
					region_.get_max() - region_.get_min();

				if (is_less(cube_params.get_x(), MIN_SIZE) &&
					is_less(cube_params.get_y(), MIN_SIZE) &&
					is_less(cube_params.get_z(), MIN_SIZE)) {
					return;
				}

				std::array<Cube<FloatType>, 8> cubes;
				region_.partition(cubes);
				std::array<triangles_list, 8> triangles_partition;
				std::list<typename triangles_list::iterator> triangles_deletion;

				for (auto triangle_it = triangles_.begin();
					 triangle_it != triangles_.end(); triangle_it++) {
					for (int part_num = 0; part_num < 8; part_num++) {
						if (!cubes[part_num].is_triangle_in_cube(
								triangle_it->first))
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
						children_[child_num] = new Node(
							triangles_partition[child_num], cubes[child_num]);
						children_[child_num]->build_tree();
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

			void get_intersections_with_children(
				std::set<size_t>& result,
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

			void get_triangles(triangles_list& triangles) const {
				triangles.insert(triangles.begin(), triangles_.begin(),
								 triangles_.end());

				if (!has_child)
					return;

				for (auto i : children_) {
					if (i == nullptr)
						continue;
					i->get_triangles(triangles);
				}
			}

			void swap(Node& node) noexcept {
				std::swap(region_, node.region_);
				std::swap(triangles_, node.triangles_);
				std::swap(children_, node.children_);
				std::swap(has_child, node.has_child);
			}

			public:

			Node(const triangles_list& objects, const Cube<FloatType>& region) {
				region_ = region;
				triangles_ = objects;
				children_.fill(nullptr);

				build_tree();
			}

			Node(const Node& node) {
				region_ = node.region_;

				triangles_list triangles;
				node.get_triangles(triangles);

				triangles_ = triangles;

				build_tree();
			}

			Node(Node&& node) noexcept { swap(node); }

			Node& operator=(const Node& node) {
				if (this != &node) {
					Node tmp{node};

					swap(tmp);
				}

				return *this;
			}

			Node& operator=(Node&& node) noexcept {
				swap(node);

				return *this;
			}

			~Node() {
				for (Node* child : children_) {
					delete child;
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
					if (!child)
						continue;
					std::set<size_t> result_child = child->get_intersections();
					for (size_t triangle_num : result_child) {
						result.insert(triangle_num);
					}
				}

				return result;
			}
		};

		Node* root = nullptr;

		void swap(Octree& tree) noexcept { std::swap(root, tree.root); }

		public:

		Octree(const triangles_list& triangles,
			   const CubeParams<FloatType>& region) {
			root = new Node(triangles, region);
		}

		Octree(const Octree& tree) {
			if (tree.root == nullptr)
				return;

			root = new Node({}, {});
			*root = *tree.root;
		}

		Octree(Octree&& tree) noexcept { swap(tree); }

		Octree& operator=(const Octree& tree) {
			if (this != &tree) {
				Octree<FloatType> tmp{tree};

				swap(tmp);
			}

			return *this;
		}

		Octree& operator=(Octree&& tree) noexcept {
			swap(tree);

			return *this;
		}

		~Octree() { delete root; }

		std::set<size_t> get_intersections() const {
			return root->get_intersections();
		}

		const Node* get_root() const { return root; }
	};
} // namespace Octree