#pragma once
#include <array>

struct Cell {
    int value;   // 0 = unsolved
    std::array<bool, 9> possibilities; // true if the number is a possible solution for the cell
};

struct Grid {
    std::array<std::array<Cell, 9>, 9> cells;
};
