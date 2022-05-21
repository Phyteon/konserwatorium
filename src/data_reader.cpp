/*
 * This file contains definitions and implementations for anything contained in data_reader.h file.
 */
/* TODO: rewrite cmake so that no relative path is used - only header name */
#include <fstream>
#include "../inc/data_reader.h"

reader::Matrix::Matrix(std::vector<std::vector<std::string>> file_contents) {
    for (auto row{0U}; row < file_contents.size(); row++) {
        this->m.emplace_back(std::vector<reader::Node>());
        for (auto node{0U}; node < file_contents[0].size(); node++) {
            this->m[row].emplace_back(Node(file_contents[row][node]));
        }
    }
}

std::vector<std::vector<std::string>> reader::DataReader::read_csv_file(std::ifstream file_handle) {
    // TODO: Implement
    std::vector<std::vector<std::string>> buff{};
    return buff;
}