
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "utils.hpp"

#include "hex.hpp"


class Board {

    public:
        explicit Board(int N);
        ~Board() = default;

        void Build(int N);
        void Resize(int N);
        int GetSize() const;
        bool InBounds(const int q, const int r) const;





        // Accessors for Axial and Offset coordinates
        std::shared_ptr<Hex> GetTile(int q, int r) const;
        std::shared_ptr<Hex> GetTileByOffset(int row, int col) const;

        // Accessors for neighboring tiles
        std::vector<std::shared_ptr<Hex>> GetNeighbors(const Coords& coords) const;
        std::vector<std::shared_ptr<Hex>> Neighbors(int q, int r) const;


        const std::vector<std::vector<std::shared_ptr<Hex>>>& GetTiles() const;

        // print to console
        friend std::ostream& operator<<(std::ostream& os, const Board& b);

    private:
        int size_; // size
        std::vector<std::vector<std::shared_ptr<Hex>>> tiles_;


};


#endif
