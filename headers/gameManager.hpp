//
// Created by Stephen Donlin on 11/21/25.
//

#ifndef HEX_GameManager_H
#define HEX_GameManager_H

#include "board.hpp"
#include "player.h"
#include "unionFind.hpp"



class GameManager {
    // singleton to control a session of the game
    public:

        static GameManager& GetInstance() {
            return instance_;
        }
        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;

        void SetUp(int n) const;
        void InitForest() const;

//        void PrintBoard()const;

    private:
        GameManager();
        static GameManager instance_;
        std::unique_ptr<Board> board_;
        UnionFind uf_;
        int num_round_;
        //std::unique_ptr<Player> p1_;
        //std::unique_ptr<Player> p2_;


        // p1 & p2
};


#endif // HEX_GameManager_H
