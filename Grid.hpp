#pragma once
#include <array>

struct Cell {
    int value = 0;   // 0 = unsolved
    std::array<bool, 9> possibilities{}; // true if the number is a possible solution for the cell

    bool getCandidate(int n) const {
        return possibilities[n - 1];
    }

    void setCandidate(int n, bool b) {
        possibilities[n - 1] = b;
    }

    auto operator<=>(const Cell&) const = default;
};

struct Grid {
    std::array<std::array<Cell, 9>, 9> cells{};

    auto operator<=>(const Grid&) const = default;
};
