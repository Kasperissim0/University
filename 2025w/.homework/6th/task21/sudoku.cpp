#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            std::cout << grid[row][col] << " ";
            if ((col + 1) % 3 == 0 && col != 8) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if ((row + 1) % 3 == 0 && row != 8) {
            std::cout << "---------------------" << std::endl;
        }
    }
}

// Function to check if it's safe to place a number in a given cell
bool isValid(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check row
    for (int x = 0; x < 9; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < 9; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find the next empty cell (represented by 0)
// Returns true if an empty cell is found and updates row and col, false otherwise.
bool findEmptyLocation(const std::vector<std::vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Sudoku solving function for generation (with random numbers)
bool solveSudokuRandomly(std::vector<std::vector<int>>& grid) {
    int row, col;
    if (!findEmptyLocation(grid, row, col)) {
        return true;
    }

    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

    for (int num : nums) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudokuRandomly(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}


// Main Sudoku solving function using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;

    // If there is no empty cell, the Sudoku is solved
    if (!findEmptyLocation(grid, row, col)) {
        return true; // Sudoku solved
    }

    // Consider numbers from 1 to 9
    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num; // Place the number

            if (solveSudoku(grid)) {
                return true; // Recursively try to solve the rest
            }

            // If placing num doesn't lead to a solution, backtrack
            grid[row][col] = 0; // Unassign the number
        }
    }

    return false; // No number can be placed in this cell
}

void generateSudokuPuzzle(std::vector<std::vector<int>>& grid, int difficulty) {
    grid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    solveSudokuRandomly(grid); // Generate a full Sudoku

    int cellsToRemove = difficulty;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    while(cellsToRemove > 0){
        int row = std::uniform_int_distribution<>(0, 8)(gen);
        int col = std::uniform_int_distribution<>(0, 8)(gen);

        if(grid[row][col] != 0){
            grid[row][col] = 0;
            cellsToRemove--;
        }
    }
}


int main() {
    char choice;
    std::cout << "Generate a new Sudoku (g) or solve the sample (s)? ";
    std::cin >> choice;

    std::vector<std::vector<int>> grid;

    if (choice == 'g') {
        int difficulty = 40; // Default difficulty
        std::cout << "Enter number of empty cells (difficulty, e.g., 40 for medium): ";
        std::cin >> difficulty;
        if(difficulty < 1 || difficulty > 80) {
            std::cout << "Invalid difficulty. Using default (40)." << std::endl;
            difficulty = 40;
        }
        generateSudokuPuzzle(grid, difficulty);

    } else {
        // Example Sudoku puzzle (0 represents empty cells)
        grid = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };
    }

    std::cout << "\nOriginal Sudoku:\n";
    printGrid(grid);
    std::cout << "\nSolving...\n\n";

    if (solveSudoku(grid)) {
        std::cout << "Solved Sudoku:\n";
        printGrid(grid);
    } else {
        std::cout << "No solution exists for the given Sudoku.\n";
    }

    return 0;
}
