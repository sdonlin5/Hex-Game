//
// Created by Stephen Donlin on 11/26/25.
//
//

#ifndef HEX_UNIONFIND_HPP
#define HEX_UNIONFIND_HPP

#include <memory>
#include "hex.hpp"

class UnionFind {
public:
    UnionFind() = default;
    ~UnionFind() = default;

    void MakeSet(std::shared_ptr<Hex> hex);
    std::shared_ptr<Hex> FindRoot(std::shared_ptr<Hex> hex);
    void Union(std::shared_ptr<Hex> x, std::shared_ptr<Hex> y);
    void Link(std::shared_ptr<Hex> x, std::shared_ptr<Hex> y);
};

#endif //HEX_UNIONFIND_HPP