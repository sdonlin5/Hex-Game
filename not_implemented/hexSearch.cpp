//
// Created by Stephen Donlin on 11/24/25.
//

//  Hex edge numbering
//     5       0
//
// 4               1
//
//     3       2

//   point up orientation
//   center tile neighbors
//       (col, row - 1)         top left
//       (col + 1, row - 1)     top right
//       (col - 1, row)         left
//       (col + 1, row)         right
//       (col, row + 1)         bottom left
//       (col + 1, row + 1)     bottom right


#include <filesystem>
#include <qtextstream.h>
#include <__charconv/chars_format.h>

#include "hexSearch.hpp"

void HexSearch::DFS(const Board& board, const Hex& hex) const {
    std::vector<Hex> path;
    path.push_back(hex);
    std::vector<const Hex*> neighbors = GetNeighbors(board, hex);

    VisitHex(board, hex);

    for (Hex* n : neighbors) {

    }
} // dfs

vector FindConnections(Board board, Hex hex) {
    vector<hex> path                                           // return vector of connected path
    bool won;
    while (!won)                                               // while not won
        for each neighbor n in GetNeighbors(hex):
            DFS(board, n, &path, hex, &win)                   // dfs on each neighbor



void DFS(board, hex, &path, root)
    if hex.status != root.status                               // base case - not connected
        return;
    else
        hex.path.push_back(hex)                                // add the hex to the connected path

    for each neighbor n of hex:                                 // get neighbors
        DFS(board, n, &path, hex, &win)                         // recurse







void HexSearch::VisitHex(const Hex& hex, state color) const {
    if (hex.state == color) {

    }
}

std::vector<const Hex*> GetNeighbors(const Board& board, const Hex& hex) const {
    // Given a Hex tile, returns vector or neighboring tiles or nullptr to
    // invalid neighbor coordindates.

    std::vector<const Hex*> neighbors;

    const int col = hex.getCoords().col;
    const int row = hex.getCoords().row;

    neighbors.push_back(board.GetHex(col + 1, row - 1));    // 0 top left
    neighbors.push_back(board.GetHex(col + 1, row));        // 1 right side
    neighbors.push_back(board.GetHex(col + 1, row + 1));    // 2 bottom right
    neighbors.push_back(board.GetHex(col, row + 1));        // 3 bottom left
    neighbors.push_back(board.GetHex(col - 1, row));        // 4 left side
    neighbors.push_back(board.GetHex(col, row - 1));        // 5 top left
    return neighbors;
}




//   point up orientation
//   center tile neighbors
//       (col, row - 1)         top left
//       (col + 1, row - 1)     top right
//       (col - 1, row)         left
//       (col + 1, row)         right
//       (col, row + 1)         bottom left
//       (col + 1, row + 1)     bottom right
