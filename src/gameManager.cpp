//
// Created by Stephen Donlin on 11/21/25.
//

#include "../headers/gameManager.hpp"


GameManager GameManager::instance_;

GameManager::GameManager() {
    board_ = std::make_unique<Board>(11);
    num_round_ = 0;
}

bool GameManager::CheckValidMove(int q, int r, state color) {
    if (game_over_) { return false; }
    if (!board_ -> InBounds(q, r) ) { return false; }
    if (board_ -> GetTile(q, r) -> GetState() != state::kNone) { return false; }
    //if (current_player_ -> GetColor() != color) { return false; }
    return true;
}

void GameManager::UnionNeighbors(const std::shared_ptr<Hex>& hex, const std::vector<std::shared_ptr<Hex>>& neighbors) {
    // Unions neighboring hex tiles of same state
    UnionFind& uf = (hex->GetState() == state::kBlack) ? uf_black_ : uf_gold_;
    for (const std::shared_ptr<Hex>& n : neighbors) {
        if (hex -> GetState() != state::kNone && hex -> GetState() == n -> GetState()) {
            uf.Union(hex, n);
        }
    }
}

void GameManager::UnionEdge(std::shared_ptr<Hex>& played_hex, std::shared_ptr<Hex>& direction_hex) {
    UnionFind& uf = (played_hex->GetState() == state::kBlack) ? uf_black_ : uf_gold_;
    uf.Union(played_hex, direction_hex);
}

bool GameManager::CheckWin(state color) {
    // Checks for win based on color
    // Currently black is always vertical and gold always horizontal
    if (color == state::kBlack) {
        if (uf_black_.FindRoot(edge_top_) == uf_black_.FindRoot(edge_bottom_)) {
            game_over_ = true;
            winner_ = state::kBlack;
            return true;
        }
    }
    else if (color == state::kGold) {
        if (uf_gold_.FindRoot(edge_left_) == uf_gold_.FindRoot(edge_right_)) {
            game_over_ = true;
            winner_ = state::kGold;
            return true;
        }
    }
    return false;
}


bool GameManager::PlayMove(int q, int r, state color) {
    // get ptr to played tile
    if (!CheckValidMove(q, r, color)){
        return false;
    }
    auto played_tile = board_->GetTile(q, r);
    played_tile -> SetState(color);
    std::vector<std::shared_ptr<Hex>> neighbors = board_-> GetNeighbors(played_tile -> GetCoords());
    UnionNeighbors(played_tile, neighbors);

    auto [row, col] = utils::axial_to_offset(q, r);

    // updated edge unioning to account for color
    if (color == state::kGold){
        if (col == 0) UnionEdge(played_tile, edge_left_);
        if (col == board_ -> GetSize() - 1) UnionEdge(played_tile, edge_right_);
    }
    if (color == state::kBlack) {
        if (row == 0) UnionEdge(played_tile, edge_top_);
        if (row == board_ -> GetSize() - 1) UnionEdge(played_tile, edge_bottom_);
    }
    CheckWin(color);
    return true;
}

std::shared_ptr<Hex> GameManager::SetEdgeTile(int q, int r, const state color) {
    // creates virtual edges to connect
    std::shared_ptr<Hex> edge_node = std::make_shared<Hex>(q, r);
    edge_node -> SetState(color);
    return edge_node;
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

    //  Set edge tile values for fixed orientation board
    edge_top_ = SetEdgeTile(-500, -500, state::kBlack);
    edge_bottom_= SetEdgeTile(-502, -502, state::kBlack);
    uf_black_.MakeSet(edge_top_);
    uf_black_.MakeSet(edge_bottom_);

    edge_left_= SetEdgeTile(-501, -501, state::kGold);
    edge_right_= SetEdgeTile(-503, -503, state::kGold);
    uf_gold_.MakeSet(edge_left_);
    uf_gold_.MakeSet(edge_right_);

}


void GameManager::SetUp(const int n) {
    // builds n x n game board, initializes disjoint-set forest
    // used by UnionFind algorithm
    game_over_ = false;
    winner_ = state::kNone;
    num_round_ = 0;
    board_ -> Build(n);
    InitForest();
}


// TODO: Implement FirstMove() to randomize first turn
// TODO: Implement Swap() to update current player
