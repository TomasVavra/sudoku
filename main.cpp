# include <iostream>
# include <array>
# include "functions.hpp"

int main () {

// const std::array<std::array<int,9>,9> instructions = {{
//     {0,1,0,6,0,0,9,0,0},
//     {0,0,0,0,3,0,0,0,1},
//     {9,0,8,1,7,4,5,0,0},
//     {0,0,1,8,0,0,0,7,4},
//     {0,0,0,0,0,0,0,0,0},
//     {5,6,0,0,0,7,1,0,0},
//     {0,0,9,7,4,6,8,0,5},
//     {6,0,0,0,9,0,0,0,0},
//     {0,0,7,0,0,2,0,3,0},
// }};

// const std::array<std::array<int,9>,9> instructions = {{
//     {0,0,0,0,0,0,3,9,6},
//     {3,0,0,0,0,8,2,0,0},
//     {0,0,0,1,0,6,4,0,8},
//     {5,9,0,0,0,1,0,0,0},
//     {0,1,0,5,2,7,0,8,0},
//     {0,0,0,4,0,0,0,3,1},
//     {1,0,4,7,0,2,0,0,0},
//     {0,0,7,8,0,0,0,0,3},
//     {9,2,8,0,0,0,0,0,0}
// }};

const std::array<std::array<int,9>,9> instructions = {{
    {9,0,0,0,6,3,0,5,0},
    {0,0,2,0,0,1,0,9,0},
    {0,0,4,9,0,0,7,0,1},
    {0,0,6,0,1,0,0,8,0},
    {0,0,0,3,0,6,0,0,0},
    {0,1,0,0,8,0,9,0,0},
    {7,0,9,0,0,5,8,0,0},
    {0,4,0,8,0,0,2,0,0},
    {0,3,0,1,4,0,0,0,9}
}};

Grid solution;
Grid last_solution;

copy_2D_to_3d (instructions, solution);

print (solution);

std::cout << std::string(111, '*') << "\n\n";
int number_of_loops = 0;

// while (solution != last_solution)
// {
//     number_of_loops ++;
//     last_solution = solution;

//     delete_possibilities_in_row_col_square (solution);
//     delete_possibilities_in_solved_cells (solution);

    
//     check_if_only_1_cell_solution_exists (solution);
//     delete_possibilities_in_solved_cells (solution);

//     delete_possibilities_in_row_col_square (solution);
//     delete_possibilities_in_solved_cells (solution);

//     check_rows (solution);
//     delete_possibilities_in_solved_cells (solution);

//     delete_possibilities_in_row_col_square (solution);
//     delete_possibilities_in_solved_cells (solution);

//     check_cols (solution);
//     delete_possibilities_in_solved_cells (solution);

//     delete_possibilities_in_row_col_square (solution);
//     delete_possibilities_in_solved_cells (solution);

//     check_blocks (solution);
//     delete_possibilities_in_solved_cells (solution);

//     delete_possibilities_in_row_col_square (solution);
//     delete_possibilities_in_solved_cells (solution);

//     print (solution);
// }

while (solution != last_solution)
{
    number_of_loops ++;
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

    print(solution);
}



std::cout << "number_of_loops " << number_of_loops << "\n";
std::cout << "is solution valid: " << is_solution_valid (solution) << "\n";

return 0;
}