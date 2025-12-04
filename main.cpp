#include <iostream>
#include <memory>

#include "headers/board.hpp"




int main() {
    // Choose board size (3x3 or 4x4)
    const int size = 11;

    Board board(size);
    board.Build(size);

    std::cout << "\nNeighbor listing for each tile on a "
              << size << "x" << size << " board:\n\n";

    // Iterate over every tile on the board
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            // Get the tile using offset coordinates
            std::shared_ptr<Hex> tile = board.GetTileByOffset(row, col);
            Coords coords = tile->GetCoords();  // These are axial

            std::cout << "Tile " << tile->StringifyCoords()
                      << " (q=" << coords.q
                      << ", r=" << coords.r << ") has neighbors: ";

            auto neighbors = board.GetNeighbors(coords);

            if (neighbors.empty()) {
                std::cout << "(none)";
            } else {
                bool first = true;
                for (const auto& n : neighbors) {
                    if (!first) {
                        std::cout << ", ";
                    }
                    std::cout << n->StringifyCoords();
                    first = false;
                }
            }

            std::cout << "\n";
        }
    }

    std::cout << std::endl;
    return 0;
}
