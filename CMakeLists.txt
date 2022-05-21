cmake_minimum_required(VERSION 3.21)
project(konserwatorium)

set(CMAKE_CXX_STANDARD 14)

add_executable(konserwatorium main.cpp inc/solver.h inc/data_reader.h src/data_reader.cpp src/solver.cpp)
