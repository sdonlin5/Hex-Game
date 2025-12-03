//
// Created by Stephen Donlin on 11/26/25.
//

#include "../headers/unionFind.hpp"

#include <qcoreapplication.h>

void UnionFind::MakeSet(Hex& hex) {
    hex.SetSelfParent();
    hex.setRank(0);
}

void UnionFind::MakeSet(Hex& hex) {
    hex.SetSelfParent();
    hex.setRank(0);
}

Hex& UnionFind::FindRoot(std::shared_ptr<Hex> hex) {
    if (hex.GetParent().lock() == hex.shared_from_this()) {
        return *hex;
    }
}















