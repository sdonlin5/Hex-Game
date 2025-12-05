#ifndef HEX_HEX_H
#define HEX_HEX_H

#include <iostream>
#include <string>
#include <memory>

#include "column.hpp"
#include "coords.hpp"
#include "state.hpp"



class Hex {
    public:
        // Constructors / destructor
        Hex(int q, int r);
        ~Hex();

        // Coordinate accessors
        Coords GetCoords() const;
        void SetCoords(Coords coords);
        std::string StringifyCoords() const;

        // State accessors
        state GetState() const;
        void SetState(state state);

    private:
        Coords coords_ {};
        state state_ {state::kNone};
};

#endif