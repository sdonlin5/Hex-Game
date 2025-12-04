//
// Created by Stephen Donlin on 11/21/25.
//

#include <iostream>
#include <stdexcept>
#include <memory>

#include "../headers/board.hpp"

Board::Board(const int N) {
    // board constructor
    size_ = N;
    // resize the container of tile
}


const std::vector<std::vector<std::shared_ptr<Hex>>>& Board::GetTiles() const {
    return tiles_;
}

void Board::Resize(const int N) {
    // Resizes board
    size_ = N;
    tiles_.resize(N);
    for (int in = 0; in < N; in++) {
        tiles_[in].resize(N);
    }
}

int Board::GetSize() const {
    return size_;
}

std::shared_ptr<Hex> Board::GetTile(const int q, const int r) const {
    // wrapper to for q, r coordinates
    auto [row, col] = utils::axial_to_offset(q, r);
    std::shared_ptr<Hex> tiles = GetTileByOffset(row, col);
    return tiles;
}

std::shared_ptr<Hex> Board::GetTileByOffset(const int row, const int col) const {
    if (row < 0 || row >= size_ || col < 0 || col >= size_) {
        throw std::out_of_range("Tile coordinates out of range");
    }
    return tiles_[row][col];
}

std::vector<std::shared_ptr<Hex>> Board::GetNeighbors(const Coords& coords) const {
    // Wrapper to pass coordinates as argument
    return Neighbors(coords.q, coords.r);
}

std::vector<std::shared_ptr<Hex>> Board::Neighbors(const int q, const int r) const {
    // Returns vector of neighbors for coordinates (q, r)
    static const std::array<std::pair<int, int>, 6> directions = {{
        {+1,  0},  // right
        {+1, -1},  // top-right
        { 0, -1},  // top-left
        {-1,  0},  // left
        {-1, +1},  // bottom-left
        { 0, +1}   // bottom-right
    }};

    std::vector<std::shared_ptr<Hex>> neighbors;

    for (const auto& [dir_q, dir_r] : directions) {
        int neighbor_q = q + dir_q;
        int neighbor_r = r + dir_r;

        // Convert to storage coords to check bounds
        auto [row, col] = utils::axial_to_offset(neighbor_q, neighbor_r);

        if (row >= 0 && row < size_ && col >= 0 && col < size_) {
            neighbors.push_back(tiles_[row][col]);
        }
    }

    return neighbors;
}






void Board::Build(const int N) {

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            auto [q, r] = utils::offset_to_axial(row, col);
            tiles_[row][col] = std::make_shared<Hex>(q, r);
        }
    }

    // console output
    std::cout << "Generated " << N << "x" << N << " board" << std::endl;
    std::cout << *this;
    std::cout << std::endl;
}

// TODO: Refactor operator<< to use GetTiles()
std::ostream& operator<<(std::ostream& os, const Board& b) {
    // Overloads << operator to output game board
    for (int r = 0; r < b.size_; r++) {
        int indent = r * 3;
        os << std::string(indent, ' ');
        for (int q = 0; q < b.size_; q++) {
            os << b.tiles_[r][q] -> StringifyCoords() << "  ";
        }
        os << "\n";
    }
    return os;
}

// sample board layout
//
// [A1] [A2] [A3] [A4] [A5] [A6] [A7] [A8] [A9] [A10] [A11]
//    [B1] [B2] [B3] [B4] [B5] [B6] [B7] [B8] [B9] [B10] [B11]
//      [C1] [C2] [C3] [C4] [C5] [C6] [C7] [C8] [C9] [C10] [C11]
//        [D1] [D2] [D3] [D4] [D5] [D6] [D7] [D8] [D9] [D10] [D11]
//          [E1] [E2] [E3] [E4] [E5] [E6] [E7] [E8] [E9] [E10] [E11]
//            [F1] [F2] [F3] [F4] [F5] [F6] [F7] [F8] [F9] [F10] [F11]
//              [G1] [G2] [G3] [G4] [G5] [G6] [G7] [G8] [G9] [G10] [G11]
//                [H1] [H2] [H3] [H4] [H5] [H6] [H7] [H8] [H9] [H10] [H11]
//                  [I1] [I2] [I3] [I4] [I5] [I6] [I7] [I8] [I9] [I10] [I11]
//                    [J1] [J2] [J3] [J4] [J5] [J6] [J7] [J8] [J9] [J10] [J11]
//                      [K1] [K2] [K3] [K4] [K5] [K6] [K7] [K8] [K9] [K10] [K11]
