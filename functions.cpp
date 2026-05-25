# include <iostream>
# include <fstream>
#include "functions.hpp"

const int INVALID_VALUE = -1;

// Copy sudoku 2D instruction to 3D solution grid
// If there is solution for given cell all other possibilities are deleted (set to false).
void copy_2D_to_3d (const std::array<std::array<int, 9>, 9> &instructions, Grid &solution)
{
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++) {
            Cell &cell = solution.cells[row][col];
            cell.value = instructions[row][col];
            
            if (instructions[row][col] == 0) {
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

// If there is solved cell, this number can not be again in row, column or 3x3 square
// Delete all possibilities for solved cell in the same row, column and 3x3 square
void delete_possibilities_in_row_col_square (Grid &solution) 
{
    for (int row = 0; row < 9; row++) 
    {
        for (int col = 0; col < 9; col++) 
        {
            Cell &cell = solution.cells[row][col];
            if (cell.value != 0)                                // for solved cells only
            {
                for (int solved_cell_index = 0; solved_cell_index < 9; solved_cell_index++)
                {
                    solution.cells[row][solved_cell_index].set_candidate(cell.value, false); // delete the number from solved cell from all possibilities in row
                    solution.cells[solved_cell_index][col].set_candidate(cell.value, false); // delete the number from solved cell from all possibilities in column
                }
                // delete the number from all possibilities in 3x3 block
                for (int block_row = 0; block_row < 3; block_row++)
                {
                    for (int block_col = 0; block_col < 3; block_col++)
                    {
                        solution.cells[(row/3)*3 + block_row][(col/3)*3 + block_col].set_candidate(cell.value, false);
                    }
                }
            }
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

// check if the number is present in row, column or square.
// If the number is present in the row, column or square only once, it is the solution.
// Even if there are more possibilities for given cell.

// void only_once_in_rows_columns_square (Grid &solution)
// {
//     for (int row_index = 0; row_index < 9; row_index++) 
//     {
//         for (int col_index = 0; col_index < 9; col_index++) 
//         {
//             std::uint8_t &sudoku_cell = solution.cells[row][col].value;
//             for (int up_index = 1; up_index < 10; up_index++) 
//             {
//                 if ((solution[row_index][col_index][up_index] != 0) && (sudoku_cell == 0))
//                 {
//                     int counter_row = 0;
//                     int counter_col = 0;
//                     int counter_square = 0;
//                     for (int l = 0; l < 9; l++)
//                     {
//                         if (solution[row_index][l][up_index] !=0)
//                         {
//                             counter_row++;
//                         }
//                         if (solution[l][col_index][up_index] !=0)
//                         {
//                             counter_col++;
//                         }                     
//                     }
//                     for (int square_3x3_row_index = 0; square_3x3_row_index < 3; square_3x3_row_index++)
//                     {
//                         for (int square_3x3_col_index = 0; square_3x3_col_index < 3; square_3x3_col_index++)
//                         {
//                             if (solution[(row_index/3)*3 + square_3x3_row_index][(col_index/3)*3 + square_3x3_col_index][up_index] != 0)
//                             {
//                                 counter_square++;
//                             }
//                         }
//                     }

//                     if (counter_row == 1 || counter_col == 1 || counter_square == 1 )
//                     {
//                         sudoku_cell = solution[row_index][col_index][up_index];
//                     }
//                 }
//             }
//         }
//     }
// }

// Check possibilities in each row.
// If specific number is possible only in one sudoku cell in row, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_rows(Grid& solution)
{
    // For each number 1–9
    for (int possibility = 1; possibility <= 9; possibility++)
    {
        // For each row
        for (int row = 0; row < 9; ++row)
        {
            int counter = 0;
            int save_col = INVALID_VALUE;

            // Scan all columns in this row
            for (int col = 0; col < 9; ++col)
            {
                Cell& cell = solution.cells[row][col];

                // Skip solved cells
                if (cell.value != 0)
                    continue;

                // Check if this cell allows the possibility
                if (cell.is_candidate_possible(possibility))
                {
                    ++counter;
                    save_col = col;
                }
            }

            // If exactly one cell in the row can take possibility, assign it
            if (counter == 1)
                solution.cells[row][save_col].value = possibility;
        }
    }
}


// Check possibilities in each column.
// If specific number is possible only in one sudoku cell in column, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_cols (Grid &solution)
{
    // For each number 1–9
    for (int possibility = 1; possibility <= 9; possibility++)
    {      
        // For each column
        for (int col = 0; col < 9; col++) 
        {
            int counter = 0;
            int row_save = INVALID_VALUE;
            
            // Scan all rows in this column
            for (int row = 0; row < 9; row++) 
            {
                Cell &cell = solution.cells[row][col];

                // Skip solved cells
                if (cell.value != 0)
                {
                    continue;
                }
                
                // Check if this cell allows the possibility
                if (cell.is_candidate_possible(possibility))
                {
                    counter++;
                    row_save = row;
                } 
            }
            
            // If exactly one cell in the column can take possibility, assign it
            if (counter == 1)
            {
                solution.cells[row_save][col].value = possibility;
            }
        }
    }
}

// Check possibilities in each 3x3 block.
// If specific number is possible only in one sudoku cell in 3x3 block, write it to the sudoku cell
// Even if there are more possibilities for given cell
void check_blocks (Grid &solution)
{
    for (int possibility = 1; possibility <= 9; possibility++)
    {
        // Iterate over all 3x3 blocks
        for (int block_row = 0; block_row < 3; block_row++)
        {
            for (int block_col = 0; block_col < 3; block_col++)
            {
                int counter = 0;    // number of cells in the 3x3 block that can take the possibility
                int save_row = INVALID_VALUE;
                int save_col = INVALID_VALUE;
                
                // iterate inside the 3×3 block
                for (int inside_row = 0; inside_row < 3; inside_row++)
                {
                    for (int inside_col = 0; inside_col < 3; inside_col++)
                    {
                        int row = block_row * 3 + inside_row;
                        int col = block_col * 3 + inside_col;
                        Cell &cell = solution.cells[row][col];

                        // Skip solved cells
                        if (cell.value != 0)
                        {
                            continue;
                        }

                        // Check if this cell allows the possibility
                        if (cell.is_candidate_possible(possibility))
                        {
                            counter++;
                            save_row = row;
                            save_col = col;
                        }
                    }
                }
                
                // If exactly one cell in the 3x3 block can take possibility, assign it
                if (counter == 1)
                {
                    solution.cells[save_row][save_col].value = possibility;
                }
            }
        }
    }
}

// Delete all possibilities for single cell, if solution was found
void delete_obsolete_possibilities (Grid &solution)
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

// check if the solution comply with sudoku rules
bool is_solution_valid (const Grid &solution)
{
    // check rows
    for (int row_col = 0; row_col < 9; row_col++) 
    {
        // array of seen numbers
        std::array<bool, 9> row_seen = {};  // all false
        std::array<bool, 9> col_seen = {};  // all false

        for (int col_row = 0; col_row < 9; col_row++) 
        {
            // row check
            const Cell &cell_row = solution.cells[row_col][col_row];

            // value is not between 1 and 9
            if (cell_row.value < 1 || cell_row.value > 9)
                return false;
            
            // duplicate found
            if (row_seen[cell_row.value - 1])
                return false;

            row_seen[cell_row.value - 1] = true;

            // col check
            const Cell &cell_col = solution.cells[col_row][row_col];

            // value is not between 1 and 9
            if (cell_col.value < 1 || cell_col.value > 9)
                return false;
            
            // duplicate found
            if (col_seen[cell_col.value - 1])
                return false;

            col_seen[cell_col.value - 1] = true;
        }
    }
    
    // Iterate over all 3x3 blocks
    for (int block_row = 0; block_row < 3; block_row++)
    {
        for (int block_col = 0; block_col < 3; block_col++)
        {
            std::array<bool, 9> seen = {};  // all false
            
            // iterate inside the 3×3 block
            for (int inside_row = 0; inside_row < 3; inside_row++)
            {
                for (int inside_col = 0; inside_col < 3; inside_col++)
                {
                    int row = block_row * 3 + inside_row;
                    int col = block_col * 3 + inside_col;
                    const Cell &cell = solution.cells[row][col];
                
                    // value is not between 1 and 9
                    if (cell.value < 1 || cell.value > 9)
                        return false;
                    
                    // duplicate found
                    if (seen[cell.value - 1])
                        return false;

                    seen[cell.value - 1] = true;
                }
            }
        }
    }
    return true;
}