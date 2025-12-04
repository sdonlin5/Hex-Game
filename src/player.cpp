//
// Created by Stephen Donlin on 12/3/25.
//

#include "player.h"

Player::Player(std::string name, state color) : name_(name), color_(color) {};

std::string Player::GetName() {
    return name_;
}
void Player::SetName(std::string name) {
    name_ = name;
}
