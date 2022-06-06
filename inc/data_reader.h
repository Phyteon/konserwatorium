/*
 * This file contains declarations and prototypes used for reading from .csv file containing input data.
 */

#ifndef KONSERWATORIUM_DATA_READER_H
#define KONSERWATORIUM_DATA_READER_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <list>

namespace reader {
    class Node {
    private:
        std::string value;
        std::pair<int, int> coordinates;
        std::list<Node*> neighbours;
        uint64_t visit_count{};
    public:
        Node() = default;
        explicit Node(std::string value){
            this->value = value;
        }
        explicit Node(size_t row, size_t col, std::string value) {
            this->coordinates = std::make_pair(row, col);
            this->value = value;
        }

        /*
         * Getters
         */
        std::string get_value(){return this->value;}
        uint64_t get_visit_count(){return this->visit_count;}
        std::pair<size_t, size_t> get_coordinates(){return this->coordinates;}
        /*
         * Setters
         */
        void increment_visit_count(){this->visit_count++;}
        void add_neighbour(Node* neighbour){
            this->neighbours.push_back(neighbour);
            this->neighbours.sort();
            this->neighbours.unique();
        }

    };

#ifdef PROTOTYPING /* Redacted currently unused code */
    class Matrix {
    private:
        std::vector<std::vector<reader::Node>> m;
    public:
        Matrix() = default;
        /*
         * Parametric constructor, which takes rows of matrix as read from file, and creates a matrix
         * of node objects.
         */
        Matrix(std::vector<std::vector<std::string>> file_contents);
        /*
         * Since the C++ standard is CPP_14, array subscript operator is implemented as follows.
         */
        auto &operator[](std::size_t row){return this->m[row];}

    };
#endif
    class DataReader {
    private:
        /*
         * Creating the object is intentionally not allowed.
         */
        DataReader() = default;

        static std::vector<std::string> get_row(const std::string& file_line);
        static std::ifstream get_file_handle(const std::string& path);

    public:
        /*
         * Static method for extracting data from a given file. Validity of file handle should be checked outside
         * the function.
         */
        static std::vector<std::vector<std::string>> read_csv_file(const std::string& path);
        static std::map<std::pair<int, int>, Node> convert_to_map(const std::vector<std::vector<std::string>> &processed_data,
                                                      const std::string &chosen_symbol);
        static std::string parse_command_line_args(int argc, char** argv);
    };
}

#endif //KONSERWATORIUM_DATA_READER_H
