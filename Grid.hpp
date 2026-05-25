#pragma once
#include <array>
#include <cstdint>

// each cell has a value (0 if unsolved) and an array of possibilities (true if the number is still a possible solution for the cell
struct Cell {
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

struct Grid {
    std::array<std::array<Cell, 9>, 9> cells{};

    auto operator<=>(const Grid&) const = default;
};
