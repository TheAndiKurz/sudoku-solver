#pragma once

#include <memory>

struct Sudoku {
    int numbers[9][9];
};
typedef struct Sudoku Sudoku;

std::unique_ptr<Sudoku> getSudokufield(std::string filename);
void solveSudokufield(Sudoku* sudoku);
void printSudokufield(const Sudoku* sudoku);
