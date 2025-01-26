# include <iostream>
# include <fstream>

const int INVALID_VALUE = -1;

// Reads sudoku instruction, each sudoku cell contains all possible solutions for given cell
void read (const int (&instructions)[9][9], int (&solution)[9][9][10])
{
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            solution[row_index][col_index][0] = instructions[row_index][col_index];

            for (int up_index = 1; up_index <= 9; up_index++) 
            {
                if (solution[row_index][col_index][0] == 0)
                {
                    solution[row_index][col_index][up_index] = up_index;    // all possible solutions for sudoku cell
                }
                else 
                {
                    solution[row_index][col_index][up_index] = 0;
                }
            }
        }
    }
}

// write sudoku grid with all possible solutions for each cell
void write (int (&solution)[9][9][10])
{
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            for (int up_index = 0; up_index <= 9; up_index++) 
            {
                std::cout << solution[row_index][col_index][up_index];
                if (up_index == 0) {std::cout << "*";}
            }
            std::cout << " ";
            if (col_index == 2 || col_index == 5) {std::cout << "  ";}
        }
        std::cout << std::endl;
        if (row_index == 2 || row_index == 5) {std::cout << std::endl;}
    }
    std::cout << std::endl << std::endl << std::endl;
}

// compare 2 solutions
bool are_solutions_identical(const int (&solution1)[9][9][10], const int (&solution2)[9][9][10])
{
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            for (int up_index = 0; up_index <= 9; up_index++)
            {
                if (solution1[row_index][col_index][up_index] != solution2[row_index][col_index][up_index])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// copy 1st sulution into the 2nd solution
void copy_1st_solution_to_2nd(const int (&solution)[9][9][10], int (&solution_copy)[9][9][10])
{
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            for (int up_index = 0; up_index <= 9; up_index++)
            {
                solution_copy[row_index][col_index][up_index] = solution[row_index][col_index][up_index];
            }
        }
    }
}

// If there is solved cell, this function deletes the number from all possibilities in row, column and 3x3 square
void delete_possibilities_in_row_col_square (int (&solution)[9][9][10])
{
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            int& sudoku_cell = solution[row_index][col_index][0];
            if (sudoku_cell != 0)                                // for solved cells
            {
                for (int solved_cell_index = 0; solved_cell_index < 9; solved_cell_index++)
                {
                    solution[row_index][solved_cell_index][sudoku_cell] = 0;     // delete the number from solved cell in row
                    solution[solved_cell_index][col_index][sudoku_cell] = 0;     // delete the number from solved cell in column
                }
                // delete the number in 3x3 square
                for (int square_3x3_row_index = 0; square_3x3_row_index < 3; square_3x3_row_index++)
                {
                    for (int square_3x3_col_index = 0; square_3x3_col_index < 3; square_3x3_col_index++)
                    {
                        solution[(row_index/3)*3 + square_3x3_row_index][(col_index/3)*3 + square_3x3_col_index][sudoku_cell] = 0;
                    }
                }
            }
        }
    }
}

// check if there is only one possible solution for single sudoku cell and write it to the cell
void check_if_only_1_cell_solution_exists (int (&solution)[9][9][10])
{
    int winner = INVALID_VALUE;
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            int& sudoku_cell = solution[row_index][col_index][0];
            int number_of_solutions = 0;
            for (int up_index = 1; up_index <= 9; up_index++) 
            {
                if ((solution[row_index][col_index][up_index] != 0) && (sudoku_cell == 0))
                {
                    number_of_solutions++;
                    winner = solution[row_index][col_index][up_index];
                }
            }
            if (number_of_solutions == 1)
            {
                sudoku_cell = winner;
            }
        }
    }
}

// check if the number is present in row, column or square.
// If the number is present in the row, column or square only once, it is the solution.
// Even if there are more possibilities for given cell.
void only_once_in_rows_columns_square (int (&solution)[9][9][10])
{
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            int& sudoku_cell = solution[row_index][col_index][0];
            for (int up_index = 1; up_index <= 9; up_index++) 
            {
                if ((solution[row_index][col_index][up_index] != 0) && (sudoku_cell == 0))
                {
                    int counter_row = 0;
                    int counter_col = 0;
                    int counter_square = 0;
                    for (int l = 0; l < 9; l++)
                    {
                        if (solution[row_index][l][up_index] !=0)
                        {
                            counter_row++;
                        }
                        if (solution[l][col_index][up_index] !=0)
                        {
                            counter_col++;
                        }                     
                    }
                    for (int square_3x3_row_index = 0; square_3x3_row_index < 3; square_3x3_row_index++)
                    {
                        for (int square_3x3_col_index = 0; square_3x3_col_index < 3; square_3x3_col_index++)
                        {
                            if (solution[(row_index/3)*3 + square_3x3_row_index][(col_index/3)*3 + square_3x3_col_index][up_index] != 0)
                            {
                                counter_square++;
                            }
                        }
                    }

                    if (counter_row == 1 || counter_col == 1 || counter_square == 1 )
                    {
                        sudoku_cell = solution[row_index][col_index][up_index];
                    }
                }
            }
        }
    }
}

// Check possibilities in each row.
// If specific number is possible only in one box in row, write it to the box
void check_rows (int (&solution)[9][9][10])
{
    for (int up_index = 1; up_index <= 9; up_index++)
    {
        
        for (int row_index = 0; row_index < 9; row_index++) 
        {
            int counter = 0;
            int row_index_save = INVALID_VALUE;
            int col_index_save = INVALID_VALUE;
            for (int col_index = 0; col_index < 9; col_index++) 
            {
                if (solution[row_index][col_index][up_index] == up_index)
                {
                    counter++;
                    row_index_save = row_index;
                    col_index_save = col_index;
                } 
            }
            if (counter == 1)
            {
                solution[row_index_save][col_index_save][0] = up_index;
            }
        }
    }
}

void check_cols (int (&solution)[9][9][10])
{
    for (int up_index = 1; up_index <= 9; up_index++)
    {      
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            int counter = 0;
            int row_index_save = INVALID_VALUE;
            int col_index_save = INVALID_VALUE;
            for (int row_index = 0; row_index < 9; row_index++) 
            {
                if (solution[row_index][col_index][up_index] == up_index)
                {
                    counter++;
                    row_index_save = row_index;
                    col_index_save = col_index;
                } 
            }
            if (counter == 1)
            {
                solution[row_index_save][col_index_save][0] = up_index;
            }
        }
    }
}

void check_squares (int (&solution)[9][9][10])
{
    for (int up_index = 1; up_index <= 9; up_index++)
    {
        for (int chose_square_3x3_row_index = 0; chose_square_3x3_row_index < 3; chose_square_3x3_row_index++)
        {
            for (int chose_square_3x3_col_index = 0; chose_square_3x3_col_index < 3; chose_square_3x3_col_index++)
            {
                int counter = 0;
                int row_index_save = INVALID_VALUE;
                int col_index_save = INVALID_VALUE;
                for (int inside_square_3x3_row_index = 0; inside_square_3x3_row_index < 3; inside_square_3x3_row_index++)
                {
                    for (int inside_square_3x3_col_index = 0; inside_square_3x3_col_index < 3; inside_square_3x3_col_index++)
                    {
                        int row = chose_square_3x3_row_index * 3 + inside_square_3x3_row_index;
                        int col = chose_square_3x3_col_index * 3 + inside_square_3x3_col_index;
                        if (solution[row][col][up_index] == up_index)
                        {
                            counter++;
                            row_index_save = row;
                            col_index_save = col;
                        }
                    }
                }
                if (counter == 1)
                {
                    solution[row_index_save][col_index_save][0] = up_index;
                }
            }
        }
    }
}

// Delete all possibilities for single cell, if solution is found
void delete_obsolete_possibilities (int (&solution)[9][9][10])
{
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            int& sudoku_cell = solution[row_index][col_index][0];
            for (int up_index = 1; up_index <= 9; up_index++) 
            {
                if (sudoku_cell != 0)
                {
                    solution[row_index][col_index][up_index] = 0; 
                }
            }
        }
    }
}

// check if the solution comply with sudoku rules
bool is_solution_valid (const int (&solution)[9][9][10])
{
    // check rows and columns
    for (int row_index = 0; row_index < 9; row_index++) 
    {
        int sum_row = 0;
        int sum_column = 0;
        for (int col_index = 0; col_index < 9; col_index++) 
        {
            sum_row = sum_row + solution[row_index][col_index][0];
            sum_column = sum_column + solution[col_index][row_index][0];       
        }

        if (sum_row != 45)
        {
            std::cout << "error in row " << row_index << std::endl;
            return false;
        }
        if (sum_column != 45)
        {
            std::cout << "error in column " << row_index << std::endl;
            return false;
        }
    }
    
    // check 3x3 squares
    for (int chose_square_3x3_row_index = 0; chose_square_3x3_row_index < 3; chose_square_3x3_row_index++)
    {
        for (int chose_square_3x3_col_index = 0; chose_square_3x3_col_index < 3; chose_square_3x3_col_index++)
        {
            int sum_square = 0;
            for (int inside_square_3x3_row_index = 0; inside_square_3x3_row_index < 3; inside_square_3x3_row_index++)
            {
                for (int inside_square_3x3_col_index = 0; inside_square_3x3_col_index < 3; inside_square_3x3_col_index++)
                    {
                        sum_square = sum_square + solution[inside_square_3x3_row_index + 3*chose_square_3x3_row_index][inside_square_3x3_col_index + 3*chose_square_3x3_col_index][0];    // delete the number in square
                    }
            }
            if (sum_square != 45)
            {
                std::cout << "error in 3x3 square " << chose_square_3x3_row_index << " x " << chose_square_3x3_col_index << std::endl;
                return false;
            }
        }    
    }    
    return true;
}