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
            uf_.MakeSet(*col);

        }
    }
}

void GameManager::SetUp(const int n) const {
    // builds n x n game board, initializes disjoint-set forest
    // used by UnionFind algorithm
    board_->Build(n);
    InitForest();

}

//std::string GetPlayerName() {
//    std::string name;
//    std::cout << "Enter player name: ";
//    std::cin >> name;
//    return name;
//}

//void GameManager::SetPlayer(int p_num) {
//
//    switch (p_num) {
//        case 1:
//            p1_ = std::make_unique<Player>(kBlack,);
//        case 2:
//            p2_= std::make_unique<Player>();
//        default:
//            std::cerr << "Could not set player" << std::endl;
//    }
//}
//


//
// void GameManager::PrintBoard() const {
//     std::cout << *board_;
// }


//void GameManager::SetBoardSize(const int size) {
//    board_size_ = size;
//}

//void GameManager::InitializeSession() const {
//    // Gathers player information and game parameters to be used for a session of play between
//    // two human players
//
//    // get / set player names
//    // get time per turn
//}

// void GameManager::StartRound() const {
//     //
// }

//void GameManager::EndRound() const {
    //
    // records winner / loser
    // prompts if players want to play another round
//}


