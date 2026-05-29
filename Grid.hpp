#pragma once
#include <array>
#include <cstdint>
#include <functional>

// each cell has a value (0 if unsolved) and an array of possibilities (true if the number is still a possible solution for the cell)
struct Cell 
{
    std::uint8_t value = 0;   // 0 = unsolved
    std::array<bool, 9> possibilities{}; // true if the number is a possible solution for the cell

    // true if the candidate number n (1-9) is still a possible solution for this cell
    bool is_candidate_possible(int n) const
    {
        return possibilities[n - 1];
    }

    // Set the candidate number n (1-9) for this cell to true or false
    void set_candidate(int n, bool b)
    {
        possibilities[n - 1] = b;
    }

    auto operator<=>(const Cell&) const = default;
};

// 9 cells in a row, column or block
struct Cell9
{
    std::array<std::reference_wrapper<Cell>, 9> cells;

    Cell9(std::array<std::reference_wrapper<Cell>, 9> init)
        : cells(init) {}

    Cell& operator[](int index) {
        return cells[index].get();
    }

    const Cell& operator[](int index) const {
        return cells[index].get();
    }

    auto operator<=>(const Cell9&) const = default;
};


// whole sudoku grid
struct Grid 
{
    std::array<std::array<Cell, 9>, 9> cells{};

    Cell9 row_as_cell9(int row) 
    {
        std::array<std::reference_wrapper<Cell>, 9> cell_refs{};
        for (int col = 0; col < 9; col++)
        {
            cell_refs[col] = cells[row][col];
        }
        return Cell9(cell_refs);
    }

    Cell9 col_as_cell9(int col) 
    {
        std::array<std::reference_wrapper<Cell>, 9> cell_refs{};
        for (int row = 0; row < 9; row++)
            cell_refs[row] = cells[row][col];
        return Cell9(cell_refs);
    }

    Cell9 block_as_cell9(int block_row, int block_col) 
    {
        std::array<std::reference_wrapper<Cell>, 9> cell_refs{};
        int idx = 0;
        for (int inside_row = 0; inside_row < 3; inside_row++)
            for (int inside_col = 0; inside_col < 3; inside_col++)
                cell_refs[idx++] = cells[block_row*3 + inside_row][block_col*3 + inside_col];
        return Cell9(cell_refs);
    }

    auto operator<=>(const Grid&) const = default;
};
