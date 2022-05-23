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

std::vector<std::string> reader::DataReader::get_row(const std::string& file_line) {
    std::vector<std::string> row{};
    for (auto &character : file_line) {
        if (std::isalpha(character)) {
            row.push_back(std::string{character});
        }
    }
    return row;
}

std::vector<std::vector<std::string>> reader::DataReader::read_csv_file(std::ifstream file_handle) {
    std::vector<std::vector<std::string>> buff{};
    std::string line{};
    std::vector<std::string> temp;
    while (std::getline(file_handle, line)) {
        temp = DataReader::get_row(line);
        if (!temp.empty()) {
            buff.push_back(temp);
        }
    }
    return buff;
}

std::list<reader::Node> reader::DataReader::convert_to_linked_list(
        const std::vector<std::vector<std::string>> &processed_data,
        const std::string &chosen_symbol) {
    std::list<>
    for (size_t row_idx{}; row_idx < processed_data.size(); row_idx++) {
        for (size_t col_idx{}; col_idx < processed_data[0].size(); col_idx++) {

        }
    }
}