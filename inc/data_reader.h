/*
 * This file contains declarations and prototypes used for reading from .csv file containing input data.
 */

#ifndef KONSERWATORIUM_DATA_READER_H
#define KONSERWATORIUM_DATA_READER_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace reader {
    class Node {
    private:
        std::string value;
        uint64_t visit_count{};
    public:
        Node() = default;
        explicit Node(std::string value){
            this->value = value;
        }
        /*
         * Getters
         */
        std::string get_value(){return this->value;}
        uint64_t get_visit_count(){return this->visit_count;}
        /*
         * Setters
         */
        void increment_visit_count(){this->visit_count++;}

    };

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

        friend std::ostream &operator<<(std::ostream &os, const Matrix &obj);
    };

    class DataReader {
    private:
        /*
         * Creating the object is intentionally not allowed.
         */
        DataReader() = default;

    public:
        /*
         * Static method for extracting data from a given file.
         */
        static std::vector<std::vector<std::string>> read_csv_file(std::ifstream file_handle);
    };
}

#endif //KONSERWATORIUM_DATA_READER_H
