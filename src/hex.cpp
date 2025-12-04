//
// Created by Stephen Donlin on 11/21/25.
//

#include "../headers/hex.hpp"
#include "../headers/utils.hpp"


// Constructors and Destructors
Hex::Hex(const int q, const int r) {
    // Default constructor
    // Axial coordinates q: offset col, r: row
    SetCoords(Coords{q, r});
}

Hex::~Hex() = default;


// Coordinate accessors
Coords Hex::GetCoords() const {
    return coords_;
}

void Hex::SetCoords(Coords coords) {
    coords_.q = coords.q;
    coords_.r = coords.r;
}

std::string Hex::StringifyCoords() const {
    // Convert axial back to offset for display
    auto [row, col] = utils::axial_to_offset(coords_.q, coords_.r);

    // Use offset coordinates for labels
    const std::string& col_letter = column.at(col + 1);
    const std::string row_num = std::to_string(row + 1);

    return "[" + col_letter + row_num + "]";
}


// State accessors
state Hex::GetState() const {
    return state_;
}

void Hex::SetState(const state state) {
    state_ = state;
}