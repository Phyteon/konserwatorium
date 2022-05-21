# Computer-aided mathematical problem-solving: final project

## 1. The task

The goal of this project is to write a C++ program that will solve a given problem based on graph theory.
Any input data should be read from a text file, and the program can output on stdout or into another file.

Our problem is as follows:
 - matrix of dimensions MxM is the input of the program
 - matrix contains only two types of values
 - starting point is a cell from one of the edges of the matrix (1 column, M column, 1 row or M row)
 - from that point, find the route to the opposite edge, where travel is only allowed through cells of one chosen value type
 - movements are allowed in all directions (including across), as well as moving to previously visited cells

## 2. Project assumptions

 - format of the input data shall be .csv file
 - two symbols will be used to represent data (according to original task description written in Polish): * as the Sun and ( as the Moon
 - as starting edge, first column is chosen
 - as an output, program will write to stdout a complete route calculated (so that all steps taken will be visible)

## 3. Responsibilities division

TO BE DISCUSSED!

 - Filip Pawelec - reading from files, cmake, dependencies
 - Krzysztof Skomiał - algorithm implementation
 - Krzysztof Kumka - algorithm implementation
 - Zachariasz Mońka - algorithm implementation