//
// Created by Stephen Donlin on 11/21/25.
//

#include <memory>

#include "../headers/board.hpp"

Board::Board(const int size) {
    // board constructor
    size_ = size;
    // resize the container of tile
}

std::vector<std::vector<std::shared_ptr<Hex>>> Board::GetTiles() const {
    return tiles_;
}

void Board::Resize(int size) {
    tiles_.resize(size);
    for (int in = 0; in < size; in++) {
        tiles_[in].resize(size);
    }
}

const Hex& GetTile(const int col, const int row) const {
    // returns reference to Hex tile
    if (col < 0 || col >= size_ || row < 0 || row >= size_) {

    }
    return
}

void Board::Build(const int size) {
    Resize(size); // set correct size
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            tiles_[r][c] = std::make_shared<Hex>(r,c);  // create new tiles
        }
    }
    std::cout << "Generated " << size << "x" << size << " board" << std::endl;
    std::cout << *this;
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Board& b) {
    for (int r = 0; r < b.size_; r++) {
        int indent = r * 3;
        os << std::string(indent, ' ');
        for (int c = 0; c < b.size_; c++) {
            os << b.tiles_[r][c] -> StringifyCoords() << "  ";
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
