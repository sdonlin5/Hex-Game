//
// Created by Stephen Donlin on 12/3/25.
//

#include "../headers/utils.hpp"

std::pair<int, int> utils::offset_to_axial(int row, int col) {
    // Convert Offset (row, col) to odd-r axial (q, r)
    //
    int q = col - (row - (row & 1)) / 2; // compute col value
    int r = row;    // row stays same
    return {q, r};
}

std::pair<int, int> utils::axial_to_offset(int q, int r) {
    // Converts odd-r axial (q, r) to Offset (row, col)
    //
    int row = r;
    int col = q + (row - (row & 1)) / 2; // compute q
    return {row, col};
}

