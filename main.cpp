#include <iostream>
#include "inc/data_reader.h"
#include "inc/solver.h"
#define SYMBOL "*"

int main(int argc, char** argv) {
    std::map<std::pair<int, int>, reader::Node> graph_as_map;
    std::vector<std::vector<std::string>> symbol_matrix;
    std::string save_path = "../utils/out.csv";
    try {
        std::string data_file_path = reader::DataReader::parse_command_line_args(argc, argv);
        symbol_matrix = reader::DataReader::read_csv_file(data_file_path);
        graph_as_map = reader::DataReader::convert_to_map(symbol_matrix,SYMBOL);
        solver::Solver::perform_checks_and_algorithm(graph_as_map, symbol_matrix, solver::left_column);
        reader::DataReader::write_output_to_file(symbol_matrix, save_path);

    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
