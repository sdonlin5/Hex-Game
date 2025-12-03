//
// Created by Stephen Donlin on 11/21/25.
//
// Implements the Hex class representing tiles on the game board.

//


#ifndef HEX_HEX_H
#define HEX_HEX_H

#include <iostream>
#include <string>
#include <memory>

#include "column.hpp"
#include "coords.hpp"
#include "state.hpp"



class Hex : std::enable_shared_from_this<Hex> {
    public:
        Hex(const int row, const int col);
        ~Hex();
        state GetState() const;
        void SetState(state state);
        Coords GetCoords() const;
        void SetCoords(Coords coords);
        std::string StringifyCoords() const;
        void SetSelfParent();
        std::weak_ptr<Hex> GetParent() const;

        bool IsRoot() const;



        void SetRank(int rank);



    private:
        std::weak_ptr<Hex> parent_;
        int rank_ {};
        Coords coords_;
        state state_;
};


#endif //HEX_HEX_H