# include <iostream>
# include "functions.h"

int error_row = 888;
int error_column = 888;
int error_square_row = 888;
int error_square_column = 888;

// const int z[9][9] = {
// {9,0,0,0,6,3,0,5,0},
// {0,0,2,0,0,1,0,9,0},
// {0,0,4,9,0,0,7,0,1},
// {0,0,6,0,1,0,0,8,0},
// {0,0,0,3,0,6,0,0,0},
// {0,1,0,0,8,0,9,0,0},
// {7,0,9,0,0,5,8,0,0},
// {0,4,0,8,0,0,2,0,0},
// {0,3,0,1,4,0,0,0,9}
// };

const int instructions[9][9] = {
{0,1,0,6,0,0,9,0,0},
{0,0,0,0,3,0,0,0,1},
{9,0,8,1,7,4,5,0,0},
{0,0,1,8,0,0,0,7,4},
{0,0,0,0,0,0,0,0,0},
{5,6,0,0,0,7,1,0,0},
{0,0,9,7,4,6,8,0,5},
{6,0,0,0,9,0,0,0,0},
{0,0,7,0,0,2,0,3,0},
};


int main () {

int solution[9][9][10];

read (instructions, solution);
write (solution);



// s[0][1][0] = 7;

std::cout << "**********************" << std::endl;
std::cout << std::endl;

std::cout << solution[2][0][0] << std::endl;

for (int p = 0; p < 20; p++)
{
    delete_possibilities_in_row_col_square (solution);
    check_rows_columns_square (solution);
    check_if_only_1_cell_solution_exists (solution);
    write (solution);
}



is_solution_valid (error_row, error_column, error_square_row, error_square_column, solution);
std::cout << "888 no error, error_row = " << error_row << std::endl;
std::cout << "888 no error, error_column = " << error_column << std::endl;
std::cout << "888 no error, error_square_row = " << error_square_row << std::endl;
std::cout << "888 no error, error_square_column = " << error_square_column << std::endl;
std::cout << std::endl;



return 0;
}