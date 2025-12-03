//
// Created by Stephen Donlin on 11/21/25.
//

#include "../headers/gameManager.hpp"

GameManager GameManager::instance_;

GameManager::GameManager() {
    board_ = std::make_unique<Board>(11);
    num_round_ = 0;
}

void GameManager::InitForest() const {
    //  Creates single element sets of Hex tiles, sets
    //  all board tile parent = self, rank = 0
    for (const auto& row : board_ -> GetTiles()) {
        for (const auto& col : row) {
            uf_.MakeSet(col);

        }
    }
}

void GameManager::SetUp(const int n) const {
    // builds n x n game board, initializes disjoint-set forest
    // used by UnionFind algorithm
    board_->Build(n);
    InitForest();

}