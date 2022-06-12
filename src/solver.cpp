/*
 * This file contains definitions and implementations for anything contained in solver.h file.
 */
/* TODO: rewrite cmake so that no relative path is used - only header name */
#include <algorithm>
#include "solver.h"

std::list<std::pair<int, int>> solver::Solver::find_optimal_path(reader::Node* node) {

    std::list<std::pair<int, int>> return_value{};
    node->increment_visit_count();
    for (auto neighbour: node->get_neighbours()) {
        if (neighbour->get_visit_count() == 0) {
            return_value.merge(find_optimal_path(neighbour));
        }
    }
    return_value.emplace_back(node->get_coordinates());
    return return_value;
}

void solver::Solver::perform_checks_and_algorithm(std::map<std::pair<int, int>, reader::Node>& graph,
                                                  std::vector<std::vector<std::string>>& matrix,
                                                  solver::MatrixEdgeEnum edge,
                                                  bool verbosity) {
    std::list<std::pair<int, int>> entry_points;
    switch (edge) {
        case top_row:
            for (int column{}; column < matrix[0].size(); column++) {
                std::pair<int, int> candidate {0, column};
                if (graph.find(candidate) != graph.end())
                    entry_points.push_back(candidate);
            }
            break;
        case bottom_row:
            for (int column{}; column < matrix[0].size(); column++) {
                std::pair<int, int> candidate {matrix.size() - 1, column};
                if (graph.find(candidate) != graph.end())
                    entry_points.push_back(candidate);
            }
            break;
        case left_column:
            for (int row{}; row < matrix.size(); row++) {
                std::pair<int, int> candidate {row, 0};
                if (graph.find(candidate) != graph.end())
                    entry_points.push_back(candidate);
            }
            break;
        case right_column:
            for (int row{}; row < matrix.size(); row++) {
                std::pair<int, int> candidate {row, matrix[0].size() - 1};
                if (graph.find(candidate) != graph.end())
                    entry_points.push_back(candidate);
            }
            break;
    }
    if (entry_points.empty()) {
        throw std::invalid_argument("No entry point in provided matrix!");
    }
    /* Find non-overlapping paths */
    std::vector<std::list<std::pair<int, int>>> visited_coordinates;
    std::vector<std::pair<int, int>> non_overlapping_entry_points;
    for (auto& coordinates: entry_points) {
        if (graph[coordinates].get_visit_count() == 0) {
            visited_coordinates.push_back(solver::Solver::find_optimal_path(&graph[coordinates]));
            non_overlapping_entry_points.push_back(coordinates);
        }
    }
    unsigned long long element_count{};
    std::list<std::pair<int, int>> chosen_list;
    /* Log info to standard output, but save only the longest path */
    if (verbosity)
        std::cout << "All possible paths (non-overlapping) and their field count:" << std::endl;

    for (size_t idx{}; idx < visited_coordinates.size(); idx++) {
        unsigned long long temp = visited_coordinates[idx].size();
        if (temp > element_count) {
            element_count = temp;
            chosen_list = visited_coordinates[idx];
        }
        if (verbosity)
            std::printf("Entry point: row %d, column %d; Length = %d\n",
                    std::get<0>(non_overlapping_entry_points[idx]),
                            std::get<1>(non_overlapping_entry_points[idx]),
                                    temp);
    }
    /* Visualising taken path */
    for (auto& coordinates: chosen_list) {
        matrix[std::get<0>(coordinates)][std::get<1>(coordinates)] = "X";
    }
}

