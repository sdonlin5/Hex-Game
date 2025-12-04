//
// Created by Stephen Donlin on 11/21/25.
//

#include "../headers/hex.hpp"


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
    //  Returns the coordinates of hex as a string: [ColRow]
    //  Cols: Letter, Rows: Num
    const std::string& q = column.at(coords_.q + 1);
    const std::string r = std::to_string(coords_.r + 1);
    return "[" + q + r + "]";
}


// State accessors
state Hex::GetState() const {
    return state_;
}

void Hex::SetState(const state state) {
    state_ = state;
}