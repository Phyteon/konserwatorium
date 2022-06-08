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
    class Solver {
    private:
        Solver() = default;
    public:
        /*
         * Create a set of visited coordinates, which will be later used to create visual representation
         * of taken path.
         */
        static std::set<std::pair<int, int>> find_optimal_path(reader::Node node);
    };
}

#endif //KONSERWATORIUM_SOLVER_H

