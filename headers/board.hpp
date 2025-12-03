//
// Created by Stephen Donlin on 11/21/25.
//

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "hex.hpp"
#include "unionFind.hpp"


class Board {

    public:
        explicit Board(const int size);
        ~Board() = default;

        void Build(int size);
        void Resize(int size);
        const Hex& GetTile(const int col, const int row) const;
        std::vector<std::vector<std::shared_ptr<Hex>>> GetTiles() const;
        std::string Stringify(Hex& hex);




        // print to console
        friend std::ostream& operator<<(std::ostream& os, const Board& b);

    private:
        int size_; // size
        std::vector<std::vector<std::shared_ptr<Hex>>> tiles_;
        //std::vector<std::vector<HexState>> tile_states_;


};


#endif
