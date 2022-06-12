cmake_minimum_required(VERSION 3.21)

project(konserwatorium)

set(CMAKE_CXX_STANDARD 17)

add_library(data_reader src/data_reader.cpp)
add_library(shared src/shared.cpp)
add_library(solver src/solver.cpp)

target_include_directories(data_reader PUBLIC inc)
target_include_directories(shared PUBLIC inc)
target_include_directories(solver PUBLIC inc)

add_executable(konserwatorium main.cpp)

target_link_libraries(konserwatorium data_reader shared solver)
