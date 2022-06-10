/*
 * This file contains declarations and prototypes for solving the problem defined in the project.
 */

#ifndef KONSERWATORIUM_SOLVER_H
#define KONSERWATORIUM_SOLVER_H

#include <string>
#include <map>
#include <set>
#include "data_reader.h"
#include "shared.h"

namespace solver {
    typedef enum tag_MatrixEdgeEnum {top_row, bottom_row, left_column, right_column} MatrixEdgeEnum;
    class Solver {
    private:
        Solver() = default;
    public:
        /*
         * Create a set of visited coordinates, which will be later used to create visual representation
         * of taken path.
         */
        static std::list<std::pair<int, int>> find_optimal_path(reader::Node* node);
        /* Check if matrix can be entered and if entry points do not overlap. */
        static void perform_checks_and_algorithm(std::map<std::pair<int, int>, reader::Node>& graph,
                                                 std::vector<std::vector<std::string>>& matrix,
                                                 MatrixEdgeEnum edge);
    };
}

#endif //KONSERWATORIUM_SOLVER_H

