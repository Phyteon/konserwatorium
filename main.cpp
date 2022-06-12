#include <iostream>
#include "data_reader.h"
#include "solver.h"
#include "shared.h"
#define SYMBOL "*"

int main(int argc, char** argv) {
    shared::Logger::print_welcome();
    std::map<std::pair<int, int>, reader::Node> graph_as_map;
    std::vector<std::vector<std::string>> symbol_matrix;
    try {
        std::map<std::string, std::string> args = reader::DataReader::parse_command_line_args(argc, argv);
        /* If map is empty and no exception was thrown, it means that only --help was specified */
        if (args.empty())
            return 0;

        symbol_matrix = reader::DataReader::read_csv_file(args["input_data_path"]);
        graph_as_map = reader::DataReader::convert_to_map(symbol_matrix,SYMBOL);

        bool verbose_switch = true;
        if ("--verbose_off" == args["verbosity"])
            verbose_switch = false;
        solver::Solver::perform_checks_and_algorithm(graph_as_map, symbol_matrix, solver::left_column, verbose_switch);
        reader::DataReader::write_output_to_file(symbol_matrix, args["output_data_path"]);

    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
