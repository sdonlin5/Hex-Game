//
// Created by Stephen Donlin on 12/3/25.
//

#include <string>

#ifndef HEX_PLAYER_H
#define HEX_PLAYER_H

class Player {
    public:
        Player(std::string name, state color);
        ~Player() = default;
        void SetName(std::string name);
        void GetName() const;


    private:
        std::string name_;
        state color_;

}

#endif //HEX_PLAYER_H
