//
// Created by Stephen Donlin on 11/26/25.
//

#ifndef HEX_UNIONFIND_HPP
#define HEX_UNIONFIND_HPP

#include <memory>
#include "hex.hpp"
#include <unordered_map>

struct HexPtrHash {
    //  Given shared_ptr<Hex>, returns the hashed address of the managed raw pointer
     std::size_t operator()(const std::shared_ptr<Hex>& ptr) const noexcept {
         return std::hash<Hex*> {}(ptr.get());
     }
};

struct HexPtrEqual {
    //Equality check for two shared_ptr<Hex> hashed values
    bool operator()(const std::shared_ptr<Hex>& x,
                    const std::shared_ptr<Hex>& y) const noexcept {
        return x.get() == y.get();
    }
};


class UnionFind {
    // Implements a disjoint-set forest by union rank
    // Adapted from CLRS Intro to Algorithms 21.3 (pg. 568) "Disjoint-Set Forests"
    public:

        UnionFind() = default;
        ~UnionFind() = default;

        void MakeSet(std::shared_ptr<Hex> hex);
        std::shared_ptr<Hex> FindRoot(std::shared_ptr<Hex> hex);
        void Union(std::shared_ptr<Hex> x, std::shared_ptr<Hex> y);
        void Link(std::shared_ptr<Hex> root_x, std::shared_ptr<Hex> root_y);
    private:
        // Container for parent and rank
        std::unordered_map<std::shared_ptr<Hex>, std::shared_ptr<Hex>, HexPtrHash, HexPtrEqual> parent_;
        std::unordered_map<std::shared_ptr<Hex>, int, HexPtrHash, HexPtrEqual> rank_;
};

#endif //HEX_UNIONFIND_HPP