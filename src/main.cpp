#include <iostream>
#include "sudoku-solver.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <sudoku field file name>"
                  << std::endl;
    }

    auto sudokuField = getSudokufield(argv[1]);

    std::cout << "Input sudoku:" << std::endl;
    printSudokufield(sudokuField.get());

    std::cout << std::endl;
    
    std::cout << "Solved sudoku:" << std::endl;
    solveSudokufield(sudokuField.get());
}
