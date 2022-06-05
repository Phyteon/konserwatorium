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
    std::list<reader::Node> linked_list;
    /* First, allocate all node objects into the list */
    for (size_t row_idx{}; row_idx < processed_data.size(); row_idx++) {
        for (size_t col_idx{}; col_idx < processed_data[0].size(); col_idx++) {
            if(processed_data[row_idx][col_idx] == chosen_symbol)
                linked_list.emplace_back(Node(row_idx, col_idx, chosen_symbol));
        }
    }
    for (auto &node: linked_list) {
        /* For each element, go through the list again to find neighbours */
        for (auto &node_inner_loop: linked_list) {
            std::pair<size_t, size_t> node_coordinates, node_inner_loop_coordinates;
            node_coordinates = node.get_coordinates();
            node_inner_loop_coordinates = node_inner_loop.get_coordinates();
            /* If the node is not the same as the one from the top loop */
            if (node_coordinates != node_inner_loop_coordinates) {
                /* Check vertically and horizontally */
                /* Casting size_t to int64_t to avoid ambiguity */
                if (std::abs((int64_t)std::get<0>(node_coordinates) -
                        (int64_t)std::get<0>(node_inner_loop_coordinates)) == 1 ||
                        std::abs((int64_t)std::get<1>(node_coordinates) -
                            (int64_t)std::get<1>(node_inner_loop_coordinates)) == 1) {
                    node.add_neighbour(&node_inner_loop);
                    node_inner_loop.add_neighbour(&node);
                }
            }
        }
    }
    return linked_list;
}