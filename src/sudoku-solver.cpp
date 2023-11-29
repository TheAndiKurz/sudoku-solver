#include <fstream>
#include <iostream>
#include <ostream>
#include "sudoku-solver.h"

std::unique_ptr<Sudoku> getSudokufield(std::string filename) {
    std::ifstream file;

    file.open(filename);
    
    if (!file.is_open()) {
        std::cerr << "could not open file with name: " << filename << std::endl;
        exit(1);
    }
    
    auto field = std::make_unique<Sudoku>();

    for (int i = 0; i < 9; i++) {
        std::string line;
        std::getline(file, line);

        for (int j = 0; j < 9; j++) {
            char c = line[2 * j];
            
            field->numbers[i][j] = (int)c - '0';
        }
    }

    return field;
}

void getValidNumbers(Sudoku* sudoku, int row, int column, int* out_valid_numbers) {
    int mask = 0;
    for (int i = 0; i < 9; i++) {
        // check row
        int cellNum = sudoku->numbers[row][i];
        if (cellNum != 0) {
            mask |= 1 << cellNum;
        }

        // check column
        cellNum = sudoku->numbers[i][column];
        if (cellNum != 0) {
            mask |= 1 << cellNum;
        }
    }
    
    // check 3x3
    int cubeIndexRow = row - row % 3;
    int cubeIndexColumn = column - column % 3;
    for (int i = cubeIndexRow; i < cubeIndexRow + 3; i++) {
        for (int j = cubeIndexColumn; j < cubeIndexColumn + 3; j++) {
            int cellNum = sudoku->numbers[i][j];
            if (cellNum != 0) {
                mask |= 1 << cellNum;
            }
        }
    }

    
    int index = 0;
    for (int i = 1; i <= 9; i++) {
        if (mask & 1 << i) {
            continue;
        }
        out_valid_numbers[index++] = i;
    }

    out_valid_numbers[index] = 0;
}

void solveSudokufield(Sudoku* sudoku, int row, int column) {
    if (column >= 9) {
        row += 1;
        column = 0;
    }

    if (row >= 9) {
        printSudokufield(sudoku);
        return;
    }

    if (sudoku->numbers[row][column] != 0) {
        solveSudokufield(sudoku, row, column + 1);
        return;
    }

    int valid_numbers[9];

    getValidNumbers(sudoku, row, column, valid_numbers);
    
    for (int valid_number : valid_numbers) {
        if (valid_number == 0) {
            break;
        }
        sudoku->numbers[row][column] = valid_number;
        solveSudokufield(sudoku, row, column + 1);
    } 

    sudoku->numbers[row][column] = 0;
}

void solveSudokufield(Sudoku* sudoku) {
    solveSudokufield(sudoku, 0, 0);
}

void printSudokufield(const Sudoku* sudoku) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "-----------" << std::endl;
        }

        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "|";
            }
            std::cout << sudoku->numbers[i][j];
        }
        std::cout << std::endl;
    }
}

