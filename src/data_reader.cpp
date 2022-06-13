/*
 * This file contains definitions and implementations for anything contained in data_reader.h file.
 */
#include <fstream>
#include "data_reader.h"

#ifdef PROTOTYPING
reader::Matrix::Matrix(std::vector<std::vector<std::string>> file_contents) {
    for (auto row{0U}; row < file_contents.size(); row++) {
        this->m.emplace_back(std::vector<reader::Node>());
        for (auto node{0U}; node < file_contents[0].size(); node++) {
            this->m[row].emplace_back(Node(file_contents[row][node]));
        }
    }
}
#endif

std::vector<std::string> reader::DataReader::get_row(const std::string& file_line) {
    std::vector<std::string> row{};
    for (auto &character : file_line) {
        if (std::isgraph(character)) {
            row.push_back(std::string{character});
        }
    }
    return row;
}

std::vector<std::vector<std::string>> reader::DataReader::read_csv_file(const std::string& path) {
    std::vector<std::vector<std::string>> buff{};
    std::string line{};
    std::vector<std::string> temp;
    std::ifstream file_handle;
    try {
        file_handle = reader::DataReader::get_file_handle(path);
        while (std::getline(file_handle, line)) {
            temp = DataReader::get_row(line);
            if (!temp.empty()) {
                buff.push_back(temp);
            }
        }
        file_handle.close();
    }
    catch (const std::invalid_argument& e) {
        throw;
    }
    for (size_t row_idx{}; row_idx < buff.size(); row_idx++) {
        if (buff[row_idx].size() != buff.size())
            throw std::invalid_argument("Matrix size does not match!");
    }

    return buff;
}

std::map<std::pair<int, int>, reader::Node> reader::DataReader::convert_to_map(
        const std::vector<std::vector<std::string>> &processed_data, const std::string &chosen_symbol) {
    std::map<std::pair<int, int>, reader::Node> lookup_table;
    /* First, allocate all node objects into the map */
    for (size_t row_idx{}; row_idx < processed_data.size(); row_idx++) {
        for (size_t col_idx{}; col_idx < processed_data[0].size(); col_idx++) {
            if(processed_data[row_idx][col_idx] == chosen_symbol) {
                lookup_table.emplace(
                        std::make_pair(
                                std::make_pair(row_idx, col_idx),
                                Node(row_idx, col_idx, chosen_symbol)));
            }
        }
    }
    for (auto& [coor, obj]: lookup_table) {
        int row, col;
        row = std::get<0>(coor);
        col = std::get<1>(coor);
        std::pair<int, int> candidates[4] = {
                std::make_pair(row - 1, col),
                std::make_pair(row + 1, col),
                std::make_pair(row, col - 1),
                std::make_pair(row, col + 1)
        };
        for (const auto& candidate: candidates) {
            auto search_result = lookup_table.find(candidate);
            if (search_result != lookup_table.end()) {
                obj.add_neighbour(&search_result->second);
            }
        }
    }
    return lookup_table;
}

std::map<std::string, std::string> reader::DataReader::parse_command_line_args(int argc, char** argv) {
    /*
     * Very simple & basic command line args handling.
     */
    std::vector<std::string> arguments;
    std::map<std::string, std::string> return_value{};
    if (1 == argc) {
        shared::Logger::print_help();
        throw std::invalid_argument("Wrong number of command line args!");
    }
    /* Converting arguments to string objects for safety reasons */
    for (int arg_iter{}; arg_iter < argc; arg_iter++) {
        arguments.emplace_back(std::string(argv[arg_iter]));
    }
    /* If --help is present, print help and exit */
    if ("--help" == arguments[1]) {
        shared::Logger::print_help();
        return return_value;
    }
    /* If there is only one argument, and it is not --help, throw exception */
    if (2 == argc) {
        shared::Logger::print_help();
        throw std::invalid_argument("Wrong number of command line args!");
    }
    /* If there are three or more arguments we assume that the necessary paths are present */
    if (3 <= argc) {
        return_value["input_data_path"] = arguments[1];
        return_value["output_data_path"] = arguments[2];
        return_value["verbosity"] = arguments[arguments.size() - 1];
    }
    return return_value;
}

std::ifstream reader::DataReader::get_file_handle(const std::string& path) {
    std::ifstream data_file;
    data_file.open(path, std::ifstream::in);
    if (data_file.is_open()) return data_file;
    else throw std::invalid_argument("Wrong path to file or file is damaged!");
}

void reader::DataReader::write_output_to_file(std::vector<std::vector<std::string>>& solved_matrix, std::string& path) {
    std::ofstream out_file (path);
    std::string out{};
    if (out_file.is_open()) {
        for (size_t row{}; row < solved_matrix.size(); row++) {
            for (size_t col{}; col < solved_matrix[0].size(); col++) {
                out += solved_matrix[row][col] + " ";
            }
            out += "\n";
        }
        out_file << out;
        out_file.close();
    }
    else throw std::invalid_argument("Unable to save to a specified path!");
}