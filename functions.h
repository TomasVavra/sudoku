# pragma once

void read (const int (&instructions)[9][9], int (&solution)[9][9][10]);

void write (int (&solution)[9][9][10]);

void delete_possibilities_in_row_col_square (int (&solution)[9][9][10]);

void check_if_only_1_cell_solution_exists (int (&solution)[9][9][10]);

void check_rows_columns_square (int (&solution)[9][9][10]);

void is_solution_valid (int &error_row, int &error_column, int &error_square_row, int &error_square_column, int (&solution)[9][9][10]);
