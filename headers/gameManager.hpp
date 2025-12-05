#ifndef HEX_GameManager_H
#define HEX_GameManager_H

#include "board.hpp"
#include "unionFind.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "coords.hpp"


class GameManager {
        // singleton to control a session of the game
    public:
        static GameManager& GetInstance() { return instance_; }
        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;
        void SetUp(int n);
        void InitForest();
        bool PlayMove(int q, int r, state color);
        std::shared_ptr<Hex> SetEdgeTile(int q, int r, state color);
        bool CheckValidMove(int q, int r, state color);
        void UnionNeighbors(const std::shared_ptr<Hex>&hex, const std::vector<std::shared_ptr<Hex>>&neighbors);
        void UnionEdge(std::shared_ptr<Hex>& played_hex, std::shared_ptr<Hex>& direction_hex);
        bool CheckWin(state color);
        bool IsGameOver() const { return game_over_; }
        state GetWinner() const { return winner_; }
        Board* GetBoard() const { return board_.get(); }

    private:
        GameManager();
        static GameManager instance_;
        std::unique_ptr< Board > board_;
        int num_round_;
        bool game_over_ { false };
        state winner_ { state::kNone };
        UnionFind uf_black_;
        UnionFind uf_gold_;

        // sentinel edge nodes for fixed orientation game board
        std::shared_ptr<Hex> edge_top_;
        std::shared_ptr<Hex> edge_bottom_;
        std::shared_ptr<Hex> edge_left_;
        std::shared_ptr<Hex> edge_right_;
};


#endif
