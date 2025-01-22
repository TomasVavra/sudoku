# include <iostream>

// Reads sudoku instruction, each sudoku cell contains all possible solutions for given cell
void read (const int (&instructions)[9][9], int (&solution)[9][9][10])
{
    int row_index,col_index,up_index;
    for (row_index = 0; row_index < 9; row_index++) 
    {
        for (col_index = 0; col_index < 9; col_index++) 
        {
            solution[row_index][col_index][0] = instructions[row_index][col_index];

            for (up_index = 1; up_index < 10; up_index++) 
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
    int row_index,col_index,up_index;
    for (row_index = 0; row_index < 9; row_index++) 
    {
        for (col_index = 0; col_index < 9; col_index++) 
        {
            for (up_index = 0; up_index < 10; up_index++) 
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

// If there is solved cell, this function deletes the number from all possibilities in row, column and 3x3 square
void delete_possibilities_in_row_col_square (int (&solution)[9][9][10])
{
    int row_index, col_index;
    int solved_cell_index;
    int square_3x3_row_index, square_3x3_col_index;
    for (row_index = 0; row_index < 9; row_index++) 
    {
        for (col_index = 0; col_index < 9; col_index++) 
        {
            int& sudoku_cell = solution[row_index][col_index][0];
            if (sudoku_cell != 0)                                // for solved cells
            {
                for (solved_cell_index = 0; solved_cell_index < 9; solved_cell_index++)
                {
                    solution[row_index][solved_cell_index][sudoku_cell] = 0;     // delete the number from solved cell in row
                    solution[solved_cell_index][col_index][sudoku_cell] = 0;     // delete the number from solved cell in column
                }
                // delete the number in 3x3 square
                for (square_3x3_row_index = 0; square_3x3_row_index < 3; square_3x3_row_index++)
                {
                    for (square_3x3_col_index = 0; square_3x3_col_index < 3; square_3x3_col_index++)
                    {
                        solution[(row_index/3)*3 + square_3x3_row_index][(col_index/3)*3 + square_3x3_col_index][sudoku_cell] = 0;
                    }
                }
            }
        }
    }
}

// check if there is only one possible solution for sudoku cell and write it to the cell
void check_if_only_1_cell_solution_exists (int (&solution)[9][9][10])
{
    int row_index, col_index, up_index;
    int number_of_solutions;
    int winner;
    for (row_index = 0; row_index < 9; row_index++) 
    {
        for (col_index = 0; col_index < 9; col_index++) 
        {
            int& sudoku_cell = solution[row_index][col_index][0];
            number_of_solutions = 0;
            for (up_index = 1; up_index < 10; up_index++) 
            {
                if ( (sudoku_cell == 0))
                {
                    number_of_solutions++;
                    winner = solution[row_index][col_index][up_index];
                }
                if (sudoku_cell != 0)
                {
                    solution[row_index][col_index][up_index] = 0;     // if the sulution exists (sudoku_cell != 0), erase all other posible solutions 
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
// If the number is present in the row, column or square only onece, it is the solution.
// Even if there are more possibilities for given cell.
// void check_rows_columns_square (int (&solution)[9][9][10])
// {
//     int row_index,col_index,up_index;
//     int square_3x3_row_index, square_3x3_col_index;
//     int l;
//     int n_in_row,n_in_column,n_in_square;
//     for (row_index = 0; row_index < 9; row_index++) 
//     {
//         for (col_index = 0; col_index < 9; col_index++) 
//         {
//             int& sudoku_cell = solution[row_index][col_index][0];
//             for (up_index = 1; up_index < 10; up_index++) 
//             {
//                 if ((solution[row_index][col_index][up_index] != 0) && (sudoku_cell == 0))
//                 {
//                     n_in_row = 0;
//                     n_in_column = 0;
//                     n_in_square = 0;
//                     for (l = 0; l < 9; l++)
//                     {
//                         if (solution[row_index][l][up_index] !=0)
//                         {
//                             n_in_row++;
//                         }
//                         if (solution[l][col_index][up_index] !=0)
//                         {
//                             n_in_column++;
//                         }                     
//                     }
//                     for (square_3x3_row_index = 0; square_3x3_row_index < 3; square_3x3_row_index++)
//                     {
//                         for (square_3x3_col_index = 0; square_3x3_col_index < 3; square_3x3_col_index++)
//                         {
//                             if (solution[(row_index/3)*3 + square_3x3_row_index][(col_index/3)*3 + square_3x3_col_index][up_index] != 0)
//                             {
//                                 n_in_square++;
//                             }
//                         }
//                     }

//                     if (n_in_row == 1 || n_in_column == 1 || n_in_square == 1 )
//                     {
//                         sudoku_cell = solution[row_index][col_index][up_index];
//                     }
//                 }
//             }
//         }
//     }
// }

void check_rows_columns_square (int (&solution)[9][9][10])
{
    int row_index,col_index,up_index;
    int square_3x3_row_index, square_3x3_col_index;
    int l;
    int n_in_row,n_in_column,n_in_square;
    for (row_index = 0; row_index < 9; row_index++) 
    {
        for (col_index = 0; col_index < 9; col_index++) 
        {
            int& sudoku_cell = solution[row_index][col_index][0];
            for (up_index = 1; up_index < 10; up_index++) 
            {
                if ((solution[row_index][col_index][up_index] != 0) && (sudoku_cell == 0))
                {
                    n_in_row = 0;
                    n_in_column = 0;
                    n_in_square = 0;
                    for (l = 0; l < 9; l++)
                    {
                        if (solution[row_index][l][up_index] !=0)
                        {
                            n_in_row++;
                        }
                        if (solution[l][col_index][up_index] !=0)
                        {
                            n_in_column++;
                        }                     
                    }
                    for (square_3x3_row_index = 0; square_3x3_row_index < 3; square_3x3_row_index++)
                    {
                        for (square_3x3_col_index = 0; square_3x3_col_index < 3; square_3x3_col_index++)
                        {
                            if (solution[(row_index/3)*3 + square_3x3_row_index][(col_index/3)*3 + square_3x3_col_index][up_index] != 0)
                            {
                                n_in_square++;
                            }
                        }
                    }

                    if (n_in_row == 1 || n_in_column == 1 || n_in_square == 1 )
                    {
                        sudoku_cell = solution[row_index][col_index][up_index];
                    }
                }
            }
        }
    }
}

// check if the solution comply with sudoku rules
void is_solution_valid (int &error_row, int &error_column, int &error_square_row, int &error_square_column, int (&solution)[9][9][10])
{
    int row_index,col_index,k,l,m,n,sum_row,sum_column,sum_square;
    for (row_index = 0; row_index < 9; row_index++) 
    {
        sum_row = 0;
        sum_column = 0;
        for (col_index = 0; col_index < 9; col_index++) 
        {
            sum_row = sum_row + solution[row_index][col_index][0];
            sum_column = sum_column + solution[col_index][row_index][0];       
        }

        if (sum_row != 45)
        {
            error_row = row_index;
        }
        if (sum_column != 45)
        {
            error_column = row_index;
        }
    }
    
    for (k = 0; k < 3; k++)
    {
        for (l = 0; l < 3; l++)
        {
            sum_square = 0;
            for (m = 0; m < 3; m++)
            {
                for (n = 0; n < 3; n++)
                    {
                        sum_square = sum_square + solution[m + 3*k][n + 3*l][0];    // delete the number in square
                    }
            }
            if (sum_square != 45)
            {
                error_square_row = k;
                error_square_column = l;
            }
        }    
    }    
    
}