//
// Created by Stephen Donlin on 11/21/25.
//

#include "../headers/hex.hpp"


// Constructors and Destructors
Hex::Hex(const int row, const int col) {
    // default constructor sets the state to none.
    SetCoords(Coords{row, col});
    state_ = state::kNone;
}

Hex::~Hex() = default;


// Coordinate accessors
Coords Hex::GetCoords() const {
    return coords_;
}

void Hex::SetCoords(Coords coords) {
    coords_.col = coords.col;
    coords_.row = coords.row;
}

std::string Hex::StringifyCoords() const {
    // returns the coordinates of hex as a string [Row, Col]
    const std::string& col = column.at(coords_.col + 1);
    const std::string row = std::to_string(coords_.row + 1);
    return "[" + col + row + "]";
}


// State accessors
state Hex::GetState() const {
    return state_;
}

void Hex::SetState(const state state) {
    state_ = state;
}


// Union-Find helpers (parent/rank)
void Hex::SetSelfParent() {
    // sets parent as weak_ptr to self
    parent_ = weak_from_this();
}

std::weak_ptr<Hex> Hex::GetParent() const {
    return parent_;
}

void Hex::SetRank(const int rank) {
    rank_ = rank;
}
bool Hex::IsRoot() const {
    // returns true if the node is it's own root
    if (std::weak_ptr<Hex> parent = GetParent(); parent.lock() == shared_from_this()) {
        return true;
    }
    return false;
}

void Hex::SetParent(std::shared_ptr<Hex> parent) {
    parent_ = std::weak_ptr<Hex>(parent);
}




void Hex::SetSelfParent() {
    // sets parent as weak_ptr to self
    parent_ = weak_from_this();
}

void Hex::SetCoords(Coords coords) {
    coords_.col = coords.col;
    coords_.row = coords.row;
}

Coords Hex::GetCoords() const {
    return coords_;
}

void Hex::SetState(const state state) {
    state_ = state;
}

state Hex::GetState() const {
    return state_;
}


std::string Hex::StringifyCoords() const {
    // returns the coordinates of hex as a string [Row, Col]
    const std::string& col = column.at(coords_.col + 1);
    const std::string row = std::to_string(coords_.row + 1);
    return "[" + col + row + "]";
}






