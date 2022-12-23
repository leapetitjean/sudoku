# Sudoku

The goal of this project is to solve sudoku with a SAT solving method.
Here the implementation is the [Davis–Putnam–Logemann–Loveland (DPLL)](https://en.wikipedia.org/wiki/DPLL_algorithm).

# Prerequisite

    sudo apt install g++
    sudo apt install cmake

# Compilation

    mkdir build && cd build
    cmake ..
    make

# Launch

    ./sudoku <file_name>

# Data

The input data must be like the following (with an extra space at the end):

`̀ `
0 7 0 0 0 0 0 4 3 
0 4 0 0 0 9 6 1 0 
8 0 0 6 3 4 9 0 0 
0 9 4 0 5 2 0 0 0 
3 5 8 4 6 0 0 2 0 
0 0 0 8 0 0 5 3 0 
0 8 0 0 7 0 0 9 1 
9 0 2 1 0 0 0 0 5 
0 0 7 0 4 0 8 0 2 
`̀ `