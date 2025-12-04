#include <iostream>
#include <memory>

#include "headers/board.hpp"

int main() {
    // Choose board size (3x3 or 4x4)
    const int size = 26;

    //
    Board board(size);
    board.Build(size);

    std::cout << "\nNeighbor listing for each tile on a "
              << size << "x" << size << " board:\n\n";

    // Iterate over every tile on the board
    for (int r = 0; r < size; ++r) {
        for (int q = 0; q < size; ++q) {
            // Get the tile at (q, r)
            std::shared_ptr<Hex> tile = board.GetTile(q, r);
            Coords coords = tile->GetCoords();

            std::cout << "Tile " << tile->StringifyCoords()
                      << " (q=" << coords.q
                      << ", r=" << coords.r << ") has neighbors: ";

            // Use the board's GetNeighbors with axial (q, r)
            auto neighbors = board.GetNeighbors(coords.q, coords.r);

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
