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
        explicit Board(int size);
        ~Board() = default;

        void Build(int size);
        void Resize(int size);

        [[nodiscard]] int GetSize() const;
        std::shared_ptr<Hex> GetTile(int row, int col) const;
        std::vector<std::shared_ptr<Hex>> GetNeighbors(int row, int col) const;
        const std::vector<std::vector<std::shared_ptr<Hex>>>& GetTiles() const;

        // print to console
        friend std::ostream& operator<<(std::ostream& os, const Board& b);

    private:
        int size_; // size
        std::vector<std::vector<std::shared_ptr<Hex>>> tiles_;
        //std::vector<std::vector<HexState>> tile_states_;


};


#endif
