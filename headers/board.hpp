//
// Created by Stephen Donlin on 11/21/25.
//

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>

#include "hex.hpp"


class Board {

    public:
        explicit Board(int N);
        ~Board() = default;

        void Build(int N);
        void Resize(int N);

        int GetSize() const;
        std::shared_ptr<Hex> GetTile(int q, int r) const;
        std::vector<std::shared_ptr<Hex>> GetNeighbors(int q, int r) const;
        const std::vector<std::vector<std::shared_ptr<Hex>>>& GetTiles() const;

        // print to console
        friend std::ostream& operator<<(std::ostream& os, const Board& b);

    private:
        int size_; // size
        std::vector<std::vector<std::shared_ptr<Hex>>> tiles_;
        //std::vector<std::vector<HexState>> tile_states_;


};


#endif
