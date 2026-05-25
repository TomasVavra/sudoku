#pragma once
#include <array>
#include <cstdint>

// each cell has a value (0 if unsolved) and an array of possibilities (true if the number is still a possible solution for the cell)
struct Cell 
{
    std::uint8_t value = 0;   // 0 = unsolved
    std::array<bool, 9> possibilities{}; // true if the number is a possible solution for the cell


    // true if the candidate number n (1-9) is still a possible solution for this cell
    bool is_candidate_possible(int n) const {
        return possibilities[n - 1];
    }

    // Set the candidate number n (1-9) for this cell to true or false
    void set_candidate(int n, bool b) {
        possibilities[n - 1] = b;
    }

    auto operator<=>(const Cell&) const = default;
};

// row or column or 3x3 block of sudoku cells
struct Cell9 
{
    std::array<Cell*, 9> cells{};

    Cell& operator[] (int index) const
    {
        return *cells[index];
    }
    auto operator<=>(const Cell9&) const = default;
};

// whole sudoku grid
struct Grid 
{
    std::array<std::array<Cell, 9>, 9> cells{};

    Cell9 row_as_cell9(int row) 
    {
        Cell9 out;
        for (int col = 0; col < 9; col++)
            out.cells[col] = &cells[row][col];
        return out;
    }

    Cell9 col_as_cell9(int col) 
    {
        Cell9 out;
        for (int row = 0; row < 9; row++)
            out.cells[row] = &cells[row][col];
        return out;
    }

    Cell9 block_as_cell9(int block_row, int block_col) 
    {
        Cell9 out;
        int idx = 0;
        for (int inside_row = 0; inside_row < 3; inside_row++)
            for (int inside_col = 0; inside_col < 3; inside_col++)
                out.cells[idx++] = &cells[block_row*3 + inside_row][block_col*3 + inside_col];
        return out;
    }

    auto operator<=>(const Grid&) const = default;
};
