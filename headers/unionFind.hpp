//
// Created by Stephen Donlin on 11/26/25.
//

#ifndef HEX_UNIONFIND_HPP
#define HEX_UNIONFIND_HPP

#include "hex.hpp"



class UnionFind {
    public:
        UnionFind() = default;
        ~UnionFind() = default;

       static void MakeSet(Hex& hex);
       static Hex& FindRoot(std::shared_ptr<Hex> hex);


};


#endif //HEX_UNIONFIND_HPP