#!/usr/bin/python
# This file contains script to generate input for C++ program

from argparse import ArgumentParser
import time
from typing import List
import random
import csv

VERSION = "1.0.0"


def prepare_parser() -> ArgumentParser:
    """
    This function returns properly set up parser.

    :return: ArgumentParser object.
    """
    default_filename = ''.join(time.ctime(time.time()).split(" ")) + ".csv"
    parser = ArgumentParser(prog='Quadratic matrix data generator')
    parser.add_argument("dimension", type=int, help="Dimensions of quadratic matrix - just a number")
    parser.add_argument("-f", "--filename", type=str, default=default_filename, dest='filename',
                        help="Name of the file where output will be saved")
    parser.add_argument("--version", action="version", version=f"{parser.prog} {VERSION}")
    parser.add_argument("-sp", "--symbol_pair", nargs=2, default=["*", "("], dest='symbol_pair',
                        help="Two symbols that will be used in the output")
    return parser


def prepare_matrix(dim: int, symbols: tuple) -> List[List[str]]:
    """
    This function returns matrix appropriately filled with provided symbols.

    Matrix is quadratic, with provided dimensions. It is filled with data in a way
    that satisfies requirements from math project (please refer to README.md)
    :param dim: Dimension of the matrix.
    :param symbols: Tuple containing two symbols used to fill the matrix.
                    The first element is assumed to be the one 'positive' in the algorithm.
    :return: List of rows.
    """
    matrix = list()
    for rows in range(dim):
        matrix.append(list())
        for cols in range(dim):
            matrix[rows].append(random.choice(symbols))  # Filling the matrix randomly

    return matrix


# Main script


parser = prepare_parser()
namespace = parser.parse_args()  # Get command line args
dimension = namespace.dimension
filename = namespace.filename
symbol_pair = tuple(namespace.symbol_pair)

with open(filename, 'w', newline='') as file_handle:
    writer = csv.writer(file_handle, delimiter=' ')
    for row in prepare_matrix(dimension, symbol_pair):
        writer.writerow(row)


