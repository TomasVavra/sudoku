# include <iostream>
# include "functions.h"


int main () {


// const int instructions[9][9] = {
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

int solution[9][9][10];
int last_solution[9][9][10];

read (instructions, solution);
write (solution);

std::cout << "**********************" << std::endl;
std::cout << std::endl;

while (! are_solutions_identical(solution, last_solution))
{
    copy_1st_solution_to_2nd(solution, last_solution);

    delete_possibilities_in_row_col_square (solution);
    delete_obsolete_possibilities (solution);

    // only_once_in_rows_columns_square (solution);
    // delete_obsolete_possibilities (solution);
    
    // check_rows (solution);
    // delete_obsolete_possibilities (solution);
    
    // check_cols (solution);
    // delete_obsolete_possibilities (solution);

    check_squares (solution);
    delete_obsolete_possibilities (solution);

    check_if_only_1_cell_solution_exists (solution);
    delete_obsolete_possibilities (solution);
    
    write (solution);
    
}

std::cout << "is solution valid: " << is_solution_valid (solution) << std::endl;

return 0;
}