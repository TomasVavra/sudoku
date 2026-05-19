# pragma once
#include "Grid.hpp"

void copy_2D_to_3d (const std::array<std::array<int, 9>, 9>& instructions, Grid &solution);

void print (const Grid &solution);

void delete_possibilities_in_row_col_square (int (&solution)[9][9][10]);

void delete_obsolete_possibilities (int (&solution)[9][9][10]);

void check_if_only_1_cell_solution_exists (int (&solution)[9][9][10]);

// void only_once_in_rows_columns_square (int (&solution)[9][9][10]);

void check_rows (int (&solution)[9][9][10]);

void check_cols (int (&solution)[9][9][10]);

void check_squares (int (&solution)[9][9][10]);

bool is_solution_valid (const int (&solution)[9][9][10]);
