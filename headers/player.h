//
// Created by Stephen Donlin on 11/24/25.
//

#ifndef HEX_PLAYER_H
#define HEX_PLAYER_H

#include <iostream>
#include <string>

#include "state.hpp"
#include "direction.h"

class Player {

    public:
        //Player(const std::string& name, hexColor color) : name_(name), color_(color) {}
        ~Player() = default;

    private:
        std::string name_;
        Direction dir_;
        state color_;

};


#endif //HEX_PLAYER_H