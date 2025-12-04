//
// Created by Stephen Donlin on 12/3/25.
//

#include "../headers/utils.hpp"
std::pair<int, int> utils::offset_to_axial(int row, int col) {
    // Convert Offset (row, col) to axial (q, r)

    int q = col;
    int r = row - (col/2);
    return {q, r};
}

std::pair<int, int> axial_to_offset(int q, int r) {
    // Convert Axial (q, r) to Offset (row, col)
    int col = q;
    int row = r + (q/2);
    return {row, col};
}
