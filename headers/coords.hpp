//
// Created by Stephen Donlin on 11/24/25.
//

#ifndef HEX_COORDS_HPP
#define HEX_COORDS_HPP

struct Coords {
    int q;    // column
    int r;    // row

    bool operator==(const Coords& other) const {
        return q == other.q && r == other.r;
    }
};

#endif //HEX_COORDS_HPP

