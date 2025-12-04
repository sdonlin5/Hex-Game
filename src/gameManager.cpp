//
// Created by Stephen Donlin on 11/21/25.
//

#include "../headers/gameManager.hpp"

GameManager GameManager::instance_;

GameManager::GameManager() {
    board_ = std::make_unique<Board>(11);
    num_round_ = 0;
}

void GameManager::InitForest() {
    //  Creates single element sets of Hex tiles, sets
    //  all board tile parent = self, rank = 0
    for (const auto& row : board_->GetTiles()) {
        for (const auto& tile : row) {
            uf_black_.MakeSet(tile);
            uf_gold_.MakeSet(tile);
        }
    }
    // Edge nodes for black
    black_top_ = std::make_shared<Hex>(-1, -1);
    black_bottom_ = std::make_shared<Hex>(-2, -2);
    uf_black_.MakeSet(black_top_);
    uf_black_.MakeSet(black_bottom_);

    // Edge nodes for gold
    gold_left_ = std::make_shared<Hex>(-3, -3);
    gold_right_ = std::make_shared<Hex>(-4, -4);
    uf_gold_.MakeSet(gold_left_);
    uf_gold_.MakeSet(gold_right_);
}


void GameManager::SetUp(const int n) {
    // builds n x n game board, initializes disjoint-set forest
    // used by UnionFind algorithm
    board_ -> Build(n);
    InitForest();
}