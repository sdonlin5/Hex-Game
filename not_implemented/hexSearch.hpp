//
// Created by Stephen Donlin on 11/24/25.
//

#ifndef HEX_HEXSEARCH_H
#define HEX_HEXSEARCH_H
#include <vector>

#include "../headers/hex.hpp"
#include "../headers/coords.hpp"
#include "../headers/board.hpp"
#include "../headers/player.h"
#include "../headers/state.hpp"
#include "../headers/direction.h"


class HexSearch {

    public:
        HexSearch() = default;
        ~HexSearch() = default;
        void DFS(Hex& hex);
        std::vector<const Hex*> GetNeighbors(const Board& board, const Hex& hex) const;
        void VisitHex(const Hex& hex);




    private:
        std::vector<Coords> connected_path_;
        std::vector<Coords> visited_;
        bool connected_;



};


#endif //HEX_HEXSEARCH_H