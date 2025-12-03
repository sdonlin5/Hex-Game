//
// Created by Stephen Donlin on 11/26/25.
//

#include "../headers/unionFind.hpp"

#include <qcoreapplication.h>

void UnionFind::Union(std::shared_ptr<Hex> x, std::shared_ptr<Hex> y) {
    Link(FindRoot(x), FindRoot(y));
}

void UnionFind::Link(std::shared_ptr<Hex> root_x, std::shared_ptr<Hex> root_y) {
    // x < y
    if (root_x -> GetRank() < root_y -> GetRank()) {
        root_x -> SetParent(root_y);
    }
    // x > y
    else if (root_x -> GetRank() > root_y -> GetRank()) {
        root_y -> SetParent(root_x);
    }
    // equal rank
    else {
        root_y -> SetParent(root_x);
        root_x -> SetRank(root_x -> GetRank() + 1);
    }
}

void UnionFind::MakeSet(std::shared_ptr<Hex> hex) {
    hex -> SetSelfParent();
    hex -> SetRank(0);
}

std::shared_ptr<Hex> UnionFind::FindRoot(std::shared_ptr<Hex> hex) {
    // ReSharper disable once CppLocalVariableMayBeConst
    // ReSharper disable once CppTooWideScopeInitStatement
    std::weak_ptr<Hex> parent = hex -> GetParent();
    // check if root
    if (parent.lock() == hex -> shared_from_this()) {
        return hex;
    }
    // recurse on the parent of the node if not root
    std::shared_ptr<Hex> root = FindRoot(parent.lock());

    // compress the path
    hex -> SetParent(root);
    return root;
}