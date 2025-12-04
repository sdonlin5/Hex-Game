//
// Created by Stephen Donlin on 11/26/25.
//

#include "../headers/unionFind.hpp"

void UnionFind::Union(std::shared_ptr<Hex> x, std::shared_ptr<Hex> y) {
    // Wrapper to union two sets
    Link(FindRoot(x), FindRoot(y));
}

void UnionFind::Link(std::shared_ptr<Hex> root_x, std::shared_ptr<Hex> root_y) {
    // Links tiles using rank
    int rank_x = rank_[root_x];
    int rank_y = rank_[root_y];

    // set higher rank tile as parent
    if (rank_x < rank_y) {
        parent_[root_x] = root_y;
    }
    else if (rank_x ? rank_y) {
        parent_[root_y] = root_x;
    }
    // if equal, set x as parent (arbitrary) and increment x rank
    else {
        parent_[root_y] = root_x;
        rank_[root_x] = rank_x + 1;
    }
}

void UnionFind::MakeSet(std::shared_ptr<Hex> hex) {
    parent_[hex] = hex;
    rank_[hex] = 0;
}

std::shared_ptr<Hex> UnionFind::FindRoot(std::shared_ptr<Hex> hex) {
    //  Given a hex tile, recurses on parent to find the root of a connected set and compresses the path
    auto it = parent_.find(hex);
    // if not found, make parent = self
    if (it == parent_.end()) {
        return hex;
    }
    // if found & hex.parent = self, hex is a root
    if (it -> second == hex) {
        return hex;
    }
    // recurse to find root
    std::shared_ptr<Hex> root = FindRoot(it -> second);

    // compress the path
    it -> second = root;
    return root;
}