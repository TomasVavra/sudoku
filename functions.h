# pragma once



void read (const int (&instructions)[9][9], int (&solution)[9][9][10]);

void write (int (&solution)[9][9][10]);

bool are_solutions_identical(const int (&solution1)[9][9][10], const int (&solution2)[9][9][10]);

void copy_1st_solution_to_2nd(const int (&solution)[9][9][10], int (&solution_copy)[9][9][10]);

void delete_possibilities_in_row_col_square (int (&solution)[9][9][10]);

void delete_obsolete_possibilities (int (&solution)[9][9][10]);

void check_if_only_1_cell_solution_exists (int (&solution)[9][9][10]);

// void only_once_in_rows_columns_square (int (&solution)[9][9][10]);

void check_rows (int (&solution)[9][9][10]);

void check_cols (int (&solution)[9][9][10]);

void check_squares (int (&solution)[9][9][10]);

bool is_solution_valid (const int (&solution)[9][9][10]);
