#include <iostream>
#include <memory>

#include "headers/board.hpp"

int main() {
    // Choose board size (3x3 or 4x4)
    const int size = 4;

    //
    Board board(size);
    board.Build(size);

    std::cout << "\nNeighbor listing for each tile on a "
              << size << "x" << size << " board:\n\n";

    // Iterate over every tile on the board
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            // Get the tile at (row, col)
            std::shared_ptr<Hex> tile = board.GetTile(row, col);
            Coords coords = tile->GetCoords();

            std::cout << "Tile " << tile->StringifyCoords()
                      << " (row=" << coords.row
                      << ", col=" << coords.col << ") has neighbors: ";

            // Use the board's GetNeighbors with (row, col)
            auto neighbors = board.GetNeighbors(coords.row, coords.col);

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
