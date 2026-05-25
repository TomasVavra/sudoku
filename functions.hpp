# pragma once
#include "Grid.hpp"

void copy_2D_to_3d (const std::array<std::array<int, 9>, 9>& instructions, Grid &solution);

void print (const Grid &solution);

void delete_possibilities_in_row_col_square (Grid &solution);

void delete_possibilities_in_solved_cells (Grid &solution);

void check_if_only_1_cell_solution_exists (Grid &solution);

bool number_in_9_cells(const Cell9& cell9, int n);

void check_rows (Grid &solution);

void check_cols (Grid &solution);

void check_blocks (Grid &solution);

bool is_solution_valid (const Grid &solution);
