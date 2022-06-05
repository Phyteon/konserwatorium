#include <iostream>
#include "inc/data_reader.h"
#define SYMBOL "*"

int main(int argc, char** argv) {
    std::list<reader::Node> graph_as_linked_list;
    try {
        std::string data_file_path = reader::DataReader::parse_command_line_args(argc, argv);
        std::vector<std::vector<std::string>> symbol_matrix = reader::DataReader::read_csv_file(data_file_path);
        graph_as_linked_list = reader::DataReader::convert_to_linked_list(symbol_matrix,
                                                                          SYMBOL);
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }


    return 0;
}
