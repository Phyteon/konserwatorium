# Computer-aided mathematical problem-solving: final project

## 1. The task

The goal of this project is to write a C++ program that will solve a given problem based on graph theory.
Any input data should be read from a text file, and the program can output on stdout or into another file.

Our problem is as follows:
 - matrix of dimensions MxM is the input of the program
 - matrix contains only two types of values
 - starting point is a cell from one of the edges of the matrix (1 column, M column, 1 row or M row)
 - from that point, find the route meeting certain conditions, where travel is only allowed through cells of one chosen value type
 - movements are allowed only to neighbouring cells (but not diagonally), including moving to previously visited cells
 - the conditions of the route are: number of moves doesn't matter, only the number of visited cells of given type matter, 
   route must lead to the same edge as the starting edge

## 2. Project assumptions

 - format of the input data shall be .csv file
 - two symbols will be used to represent data (according to original task description written in Polish): * as the Sun and ( as the Moon
 - as starting edge, first column is chosen
 - as an output, program will write to stdout a complete route calculated (so that all steps taken will be visible)

## 3. Responsibilities division

 - Filip Pawelec - reading from files, cmake, dependencies
 - Krzysztof Skomiał - algorithm implementation
 - Krzysztof Kumka - algorithm implementation
 - Zachariasz Mońka - algorithm implementation

## How to build and run the project

The project was build & tested on standard MinGW toolchain for Windows, utilising Cmake as basis
for generating necessary environment and Ninja as build system. The setup is as follows:

1. Please make sure that You have all the necessary tools with correct versions - they don't
have to be identical, but they have to be compatible:

- CMake version 3.21.0-rc3
- Ninja, release 1.11.0
- MinGW g++ version 9.2.0
- MinGW gcc version 9.2.0

2. If the project is being set up for the first time, please fire up the terminal in the project directory and
type in the following command:

```commandline
cmake -S . -B cmake-build-release-mingw -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=<path_to_build_program> -DCMAKE_C_COMPILER=<path_to_c_compiler> -DCMAKE_CXX_COMPILER=<path_to_cxx_compiler> -G Ninja .
```

3. If the above command has completed, the next command can be typed:
```commandline
cmake --build cmake-build-release-mingw --target konserwatorium
```