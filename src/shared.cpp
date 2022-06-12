//
// Created by pawel on 11/06/2022.
//

#include <iostream>
#include "shared.h"

void shared::Logger::print_welcome() {
    std::cout << "MFCP - Most Fields Counting Program - version 1.0" << std::endl;
    std::cout << "Created by: Filip Pawelec,\n Zachariasz Monka,\n Krzysztof Skomial,\n Krzysztof Kumka" << std::endl;
    std::cout << "Please read the README before using the program." << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
}

void shared::Logger::print_help() {
    std::cout << "Usage:\nkonserwatorium.exe [--help] <path_to_input_data_file> <path_to_output_data_file> [--verbose_off]" << std::endl;
    std::cout << "--help: Print this info and exit." << std::endl;
    std::cout << "Both paths are required arguments and must be valid Windows paths. Globs are not supported!" << std::endl;
    std::cout << "Optional argument --verbose_off turns off the logging of all possible (non-overlapping) paths." << std::endl;
    std::cout << "Argument parsing is done very simply, so argument positions must be preserved!" << std::endl;
}
