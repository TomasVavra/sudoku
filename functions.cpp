# include <iostream>
# include <fstream>
#include "functions.hpp"

const int INVALID_VALUE = -1;

// Copy sudoku 2D instruction to 3D solution grid
// If there is solution for given cell all possibilities are deleted (set to false)
// For unsolve cells we start with all possibilities (set to true) and delete them during the solving process
void copy_2D_to_3d (const std::array<std::array<int, 9>, 9> &instructions, Grid &solution)
{
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++) {
            Cell &cell = solution.cells[row][col];
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
void print (const Grid &solution)
{
    for (int row = 0; row < 9; row++) 
    {
        for (int col = 0; col < 9; col++) 
        {
            const Cell &cell = solution.cells[row][col];
            
            std::cout << (int)cell.value << "*";
            
            for (int candidate = 1; candidate <= 9; candidate++) 
            {
                if (cell.is_candidate_possible(candidate))
                {
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
void delete_possibilities_in_solved_cells (Grid &solution)
{
    for (int row = 0; row < 9; row++) 
    {
        for (int col = 0; col < 9; col++) 
        {
            Cell &cell = solution.cells[row][col];
            if (cell.value != 0)
            {
                cell.possibilities.fill(false);
            }
        }
    }
}

// If there is solved cell, this number can not be again in row, column or 3x3 square
// Delete all possibilities for solved cell in the same row, column and 3x3 square
void delete_possibilities_in_row_col_square (Grid &solution) 
{
    for (int row = 0; row < 9; row++) 
    {
        for (int col = 0; col < 9; col++) 
        {
            // current cell
            Cell &cell = solution.cells[row][col];

            if (cell.value == 0)    // skip solved cells
                continue;
            
            // eliminate from current row
            Cell9 row_view = solution.row_as_cell9(row);
            for (int i = 0; i < 9; i++)
                row_view[i].set_candidate(cell.value, false);

            // eliminate from current column
            Cell9 col_view = solution.col_as_cell9(col);
            for (int i = 0; i < 9; i++)
                col_view[i].set_candidate(cell.value, false);

            // eliminate from current block
            Cell9 block_view = solution.block_as_cell9(row / 3, col / 3);
            for (int i = 0; i < 9; i++)
                block_view[i].set_candidate(cell.value, false);
        }
    }
}

// check if there is only one possible solution for single sudoku cell and write it to the cell
void check_if_only_1_cell_solution_exists (Grid &solution)
{
    for (int row = 0; row < 9; row++) 
    {
        for (int col = 0; col < 9; col++) 
        {
            Cell &cell = solution.cells[row][col];
            
            // skip already solved cells
            if (cell.value != 0)
            {
                continue;
            }
            
            int number_of_solutions = 0;
            int winner = 0;

            for (int possibility = 1; possibility <= 9; possibility++) 
            {
                if (cell.is_candidate_possible(possibility))
                {
                    number_of_solutions++;
                    winner = possibility;
                }
            }
            if (number_of_solutions == 1)
            {
                cell.value = winner;
            }
        }
    }
}

// Check if specific number n is already in the 9 cells (row, column or block)
bool number_in_9_cells(const Cell9& cell9, int n)
{
    for (int i = 0; i < 9; i++)
    {
        if (cell9[i].value == n)
            return true;
    }
    return false;
}

// Check if specific number is possible only in one cell in the group of 9 cells (row, column or block)
// If there is only one cell that can take the possibility, assign it to the cell
// Even if there are more possibilities for given cell
void check_cell9_group(Cell9& group, int possibility)
{
    // Skip if n already appears in this group
    if (number_in_9_cells(group, possibility))
        return;

    int count = 0;
    int last_i = INVALID_VALUE;

    // Find all cells that can take the possibility
    for (int i = 0; i < 9; i++)
    {
        const Cell& cell = group[i];
        
        // Skip solved cells
        if (cell.value != 0)
            continue;

        if (cell.is_candidate_possible(possibility))
        {
            count++;
            last_i = i;
        }
    }

    // If exactly one cell in the row can take possibility, assign it
    if (count == 1)
        group[last_i].value = possibility;
}

// Check possibilities in each row.
// If specific number is possible only in one sudoku cell in row, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_rows(Grid& solution)
{
    for (int possibility = 1; possibility <= 9; possibility++)
    {
        for (int row = 0; row < 9; row++)
        {
            // row as Cell9 view
            Cell9 row_view = solution.row_as_cell9(row);
            check_cell9_group(row_view, possibility);
        }
    }
}

// Check possibilities in each column.
// If specific number is possible only in one sudoku cell in column, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_cols(Grid& solution)
{
    for (int possibility = 1; possibility <= 9; possibility++)
    {
        for (int col = 0; col < 9; col++)
        {
            // Column as Cell9 view
            Cell9 col_view = solution.col_as_cell9(col);
            check_cell9_group(col_view, possibility);
        }
    }
}


// Check possibilities in each 3x3 block.
// If specific number is possible only in one sudoku cell in 3x3 block, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_blocks(Grid& solution)
{
    for (int possibility = 1; possibility <= 9; possibility++)
    {
        // Iterate over the 3×3 blocks
        for (int block_row = 0; block_row < 3; block_row++)
        {
            for (int block_col = 0; block_col < 3; block_col++)
            {
                // Block as Cell9 view
                Cell9 block_view = solution.block_as_cell9(block_row, block_col);
                check_cell9_group(block_view, possibility);
            }
        }
    }
}

// Check if there are no duplicates and all values are between 1 and 9 in the group of 9 cells (row, column or block)
bool is_group_valid(const ConstCell9& group)
{
    std::array<bool, 9> seen = {};  // all false

    for (int i = 0; i < 9; i++)
    {
        int value = group[i].value;

        // value is not between 1 and 9
        if (value < 1 || value > 9)
            return false;

        // duplicate found
        if (seen[value - 1])
            return false;

        seen[value - 1] = true;
    }

    return true;
}

// check if the solution comply with sudoku rules
bool is_solution_valid(const Grid& solution)
{
    // Check rows
    for (int row = 0; row < 9; row++)
        if (!is_group_valid(solution.row_as_cell9(row)))
            return false;

    // Check columns
    for (int col = 0; col < 9; col++)
        if (!is_group_valid(solution.col_as_cell9(col)))
            return false;

    // Check blocks
    for (int block_row = 0; block_row < 3; block_row++)
        for (int block_col = 0; block_col < 3; block_col++)
            if (!is_group_valid(solution.block_as_cell9(block_row, block_col)))
                return false;

    return true;
}