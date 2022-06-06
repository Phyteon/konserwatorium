/*
 * This file contains definitions and implementations for anything contained in data_reader.h file.
 */
/* TODO: rewrite cmake so that no relative path is used - only header name */
#include <fstream>
#include "../inc/data_reader.h"

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

std::string reader::DataReader::parse_command_line_args(int argc, char** argv) {
    /*
     * Only one argument is expected, and that is a path to data file.
     * If none is provided, the program will throw an error
     */
    if (argc != 2) {
        throw std::invalid_argument("Wrong number of command line args!");
    }
    return std::string {argv[1]};
}

std::ifstream reader::DataReader::get_file_handle(const std::string& path) {
    std::ifstream data_file;
    data_file.open(path, std::ifstream::in);
    if (data_file.is_open()) return data_file;
    else throw std::invalid_argument("Wrong path to file or file is damaged!");
}