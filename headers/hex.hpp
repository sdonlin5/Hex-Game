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



class Hex : public std::enable_shared_from_this<Hex> {
    // Fields First
        // public static constants
        // private static variables
        // private instance variables
    // Methods
        // descending importance
        // public methds first
        // private or helper after methods that calls them

    public:
        // Constructors / destructor
        Hex(int row, int col);
        ~Hex();

        // Coordinate accessors
        Coords GetCoords() const;
        void SetCoords(Coords coords);
        std::string StringifyCoords() const;

        // State accessors
        state GetState() const;
        void SetState(state state);

        // Union-Find helpers (parent/rank)
        void SetSelfParent();

        std::weak_ptr<Hex> GetParent() const;
        bool IsRoot() const;
        void SetRank(int rank);
        void SetParent(std::shared_ptr<Hex> parent);
        int GetRank() const;



    private:
        std::weak_ptr<Hex> parent_;
        int rank_ {};
        Coords coords_;
        state state_;
};

#endif //HEX_HEX_H