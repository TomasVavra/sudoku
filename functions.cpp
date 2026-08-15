# include <iostream>
# include <fstream>
#include "Grid.hpp" 
#include "functions.hpp"

const int INVALID_VALUE = -1;

// Copy sudoku 2D instruction to 3D solution grid
// If there is solution for given cell all possibilities are deleted (set to false)
// For unsolve cells we start with all possibilities (set to true) and delete them during the solving process
void copy_2D_to_3d (const std::array<std::array<int, 9>, 9>& instructions, Grid& solution) {
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++) {
            Cell& cell = solution.cells[row][col];
            cell.value = instructions[row][col];
            
            if (cell.value == 0) {
                cell.possibilities.fill(true);
            } else {
                cell.possibilities.fill(false); // delete all possibilities for solved cell
            }
        }
    }
}

// print sudoku grid with possible solutions for each cell
void print (const Grid& solution) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            const Cell& cell = solution.cells[row][col];
            
            std::cout << (int)cell.value << "*";
            
            for (int candidate = 1; candidate <= 9; candidate++) {
                if (cell.is_candidate_possible(candidate)) {
                    std::cout << candidate;
                } else {
                    std::cout << " ";
                }
            }
            std::cout << " ";

            if (col == 2 || col == 5) {
                std::cout << "| ";  // 3 columns separator
            }
        }
        std::cout << "\n";
        if (row == 2 || row == 5) {
            std::cout << std::string(111, '-') << "\n";  // 3 rows separator
        }
    }
    std::cout << "\n\n";
}

// Delete all possibilities for single cell, if solution was found
void delete_possibilities_in_solved_cells (Grid& solution) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Cell& cell = solution.cells[row][col];
            if (cell.value != 0)
            {
                cell.possibilities.fill(false);
            }
        }
    }
}

// If there is solved cell, this number can not be again in row, column or 3x3 square
// Delete all possibilities for solved cell in the same row, column and 3x3 square
void delete_possibilities_in_row_col_square (Grid& solution) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // current cell
            Cell& cell = solution.cells[row][col];

            if (cell.value == 0)    // skip solved cells
                continue;
            
            // eliminate from current row
            Cell9 row_view = solution.row_as_cell9(row);
            for (int i = 0; i < 9; i++)
                row_view.cells[i]->set_candidate(cell.value, false);

            // eliminate from current column
            Cell9 col_view = solution.col_as_cell9(col);
            for (int i = 0; i < 9; i++)
                col_view.cells[i]->set_candidate(cell.value, false);

            // eliminate from current block
            Cell9 block_view = solution.block_as_cell9(row / 3, col / 3);
            for (int i = 0; i < 9; i++)
                block_view.cells[i]->set_candidate(cell.value, false);
        }
    }
}

// check if there is only one possible solution for single sudoku cell and write it to the cell
void check_if_only_1_cell_solution_exists (Grid& solution) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Cell& cell = solution.cells[row][col];
            
            // skip already solved cells
            if (cell.value != 0) {
                continue;
            }
            
            int number_of_solutions = 0;
            int winner = 0;

            for (int possibility = 1; possibility <= 9; possibility++) {
                if (cell.is_candidate_possible(possibility)) {
                    number_of_solutions++;
                    winner = possibility;
                }
            }
            if (number_of_solutions == 1) {
                cell.value = winner;
            }
        }
    }
}

// Check if specific number n is already in the 9 cells (row, column or block)
bool number_in_9_cells(const Cell9& group, int n) {
    for (int i = 0; i < 9; i++) {
        if (group.cells[i]->value == n) {
            return true;
        }
    }
    return false;
}

// Check if specific number is possible only in one cell in the group of 9 cells (row, column or block)
// If there is only one cell that can take the possibility, assign it to the cell
// Even if there are more possibilities for given cell
void check_cell9_group(Cell9& group, int possibility) {
    // Skip if n already appears in this group
    if (number_in_9_cells(group, possibility)) {
        return;
    }

    int count = 0;
    int last_i = INVALID_VALUE;

    // Find all cells that can take the possibility
    for (int i = 0; i < 9; i++) {
        const Cell& cell = *group.cells[i];
        
        // Skip solved cells
        if (cell.value != 0) {
            continue;
        }

        if (cell.is_candidate_possible(possibility)) {
            count++;
            last_i = i;
        }
    }

    // If exactly one cell in the row can take possibility, assign it
    if (count == 1) {
        group.cells[last_i]->value = possibility;
    }
}

// Check possibilities in each row.
// If specific number is possible only in one sudoku cell in row, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_rows(Grid& solution) {
    for (int possibility = 1; possibility <= 9; possibility++) {
        for (int row = 0; row < 9; row++) {
            // row as Cell9 view
            Cell9 row_view = solution.row_as_cell9(row);
            check_cell9_group(row_view, possibility);
        }
    }
}

// Check possibilities in each column.
// If specific number is possible only in one sudoku cell in column, write it to the sudoku cell
void check_cols(Grid& solution) {
    for (int possibility = 1; possibility <= 9; possibility++) {
        for (int col = 0; col < 9; col++) {
            // Column as Cell9 view
            Cell9 col_view = solution.col_as_cell9(col);
            check_cell9_group(col_view, possibility);
        }
    }
}

// Check possibilities in each 3x3 block.
// If specific number is possible only in one sudoku cell in 3x3 block, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_blocks(Grid& solution) {
    for (int possibility = 1; possibility <= 9; possibility++) {
        // Iterate over the 3×3 blocks
        for (int block_row = 0; block_row < 3; block_row++) {
            for (int block_col = 0; block_col < 3; block_col++) {
                // Block as Cell9 view
                Cell9 block_view = solution.block_as_cell9(block_row, block_col);
                check_cell9_group(block_view, possibility);
            }
        }
    }
}

// Check if there are any empty cells in the grid (value = 0) and no possibilities left for that cell
bool has_empty_cell(const Grid& solution) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            const Cell& cell = solution.cells[row][col];
            if (cell.value != 0) continue;

            bool any_possible = false;
            for (int possibility = 1; possibility <= 9; possibility++) {
                if (cell.is_candidate_possible(possibility)) {
                    any_possible = true;
                    break;
                }
            }
            if (!any_possible) return true;
        }
    }
    return false;
}

// Check if there are any duplicates in the 9 cells, ignore unsolved cells (value = 0)
bool has_cell9_duplicates(const ConstCell9& group) {
    std::array<bool, 9> seen = {};  // all false

    for (int i = 0; i < 9; i++) {
        int value = group.cells[i]->value;

        if (value == 0) {
            continue; // ignore unsolved cells
        }

        if (seen[value - 1]) {
            return true; // duplicate found
        }

        seen[value - 1] = true;
    }
    return false;
}

// Check if there are any duplicates in the sudoku grid, ignore unsolved cells (value = 0)
bool has_sudoku_duplicates(const Grid& solution) {
    // Check rows
    for (int row = 0; row < 9; row++) {
        if (has_cell9_duplicates(solution.row_as_cell9(row))) {
            std::cout << "Duplicate in row: " << row << "\n";
            return true;
        }
    }

    // Check columns
    for (int col = 0; col < 9; col++) {
        if (has_cell9_duplicates(solution.col_as_cell9(col))) {
            std::cout << "Duplicate in column: " << col << "\n";
            return true;
        }
    }

    // Check blocks
    for (int block_row = 0; block_row < 3; block_row++) {
        for (int block_col = 0; block_col < 3; block_col++) {
            if (has_cell9_duplicates(solution.block_as_cell9(block_row, block_col))) {
                std::cout << "Duplicate in block: "
                          << block_row << "," << block_col << "\n";
                return true;
            }
        }
    }

    return false; // no duplicates anywhere
}

// check if the solution comply with sudoku rules
bool is_solution_valid(const Grid& solution) {
    // Check if all cells have values between 1 and 9
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int v = solution.cells[row][col].value;
            if (v < 1 || v > 9) {
                return false;
            }
        }
    }
    
    if (has_sudoku_duplicates(solution)) {
        return false;
    }
    return true;
}



// Main solving function
// Propagate the solution by eliminating possibilities and assigning values until no further changes can be made
void propagate(Grid& solution) {
    Grid last_solution;
    
    while (solution != last_solution) {
            last_solution = solution;

            // Phase A: eliminate
            delete_possibilities_in_row_col_square(solution);
            delete_possibilities_in_solved_cells(solution);

            // Phase B: assign
            check_if_only_1_cell_solution_exists(solution);
            check_rows(solution);
            check_cols(solution);
            check_blocks(solution);

            // Phase C: eliminate again
            delete_possibilities_in_row_col_square(solution);
            delete_possibilities_in_solved_cells(solution);

            //print(solution);
        }
}

// Find the cell with the lowest number of possible solutions (candidates) in the grid
Coordinates lowest_number_of_solutions(Grid& solution) {
    Coordinates best_cell_coords = {-1, -1};
    int lowest_number_of_solutions = 10;    // // higher than any possible number of candidates
    
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            
            const Cell& cell = solution.cells[row][col];
        
            // skip already solved cells
            if (cell.value != 0) {
                continue;
            }

            int number_of_solutions = 0;
            for (int possibility = 1; possibility <= 9; possibility++) {
                if (cell.is_candidate_possible(possibility)) {
                    number_of_solutions++;
                }
            }

            if (number_of_solutions < lowest_number_of_solutions) {
                lowest_number_of_solutions = number_of_solutions;
                best_cell_coords = {row, col};
            }
        }
    }
    return best_cell_coords;   // {-1, -1} if the grid is fully solved
}

// Backtracking algorithm to solve the Sudoku puzzle
// It recursively tries all possible candidates for the cell with the fewest possibilities
// If a candidate leads to a valid solution, it returns true and updates the solution grid
bool backtracking(Grid& solution) {
    // First propagate all logical deductions
    propagate(solution);

    // If the grid is invalid, stop
    if (has_sudoku_duplicates(solution) || has_empty_cell(solution)) {
        return false;
    }

    // If fully solved, we are done
    if (is_solution_valid(solution)) {
        return true;
    }

    // Find the best cell to guess (fewest candidates)
    Coordinates coords = lowest_number_of_solutions(solution);
    if (coords.row == -1 || coords.col == -1) {
        return false; // no unsolved cells but not valid → contradiction
    }

    Cell& cell = solution.cells[coords.row][coords.col];

    // Try each candidate
    for (int possibility = 1; possibility <= 9; possibility++) {
        
        // Skip if this candidate is not possible for the cell
        if (!cell.is_candidate_possible(possibility)) {
            continue;
        }

        // Create a branch
        Grid branch = solution;

        // Assign guess
        branch.cells[coords.row][coords.col].value = possibility;
        branch.cells[coords.row][coords.col].possibilities.fill(false);

        // Recursively solve the branch
        if (backtracking(branch)) {
            solution = branch;   // copy solved branch back
            return true;
        }
    }

    // All candidates failed → dead end
    return false;
}
