//
// Created by Stephen Donlin on 12/4/25.
//

#ifndef HEX_HEXBOARD_HPP
#define HEX_HEXBOARD_HPP

#include <QGraphicsScene>
#include <QTimer>
// Sound support commented out - can be re-enabled later
//#include <QSoundEffect>
#include <memory>
#include <unordered_map>

#include "hexTile.hpp"
#include "gameManager.hpp"
#include "coords.hpp"

// Hash function for Coords in unordered_map
struct CoordsHash {
    std::size_t operator()(const Coords& c) const {
        return std::hash<int>()(c.q) ^ (std::hash<int>()(c.r) << 1);
    }
};

class HexBoard : public QObject {
    Q_OBJECT

public:
    explicit HexBoard(QGraphicsScene* scene, int boardSize = 11, qreal hexRadius = 40.0, QObject* parent = nullptr);
    ~HexBoard();

    // Board management
    void InitializeBoard(int size);
    void ResetBoard();
    void ClearBoard();

    // Game control
    void StartGame();
    void PauseGame();
    void ResumeGame();

    // Getters
    state GetCurrentPlayer() const { return currentPlayer_; }
    int GetTimeRemaining() const { return timeRemaining_; }
    bool IsGameActive() const { return gameActive_; }
    QRectF GetBoardBounds() const;

    // Called by HexTile when clicked
    void OnTileClicked(int q, int r);

signals:
    void TileClicked(int q, int r);
    void MoveCompleted(int player, bool validMove);
    void GameOver(int winner);
    void TimerTick(int secondsRemaining);
    void TurnChanged(int newPlayer);

private slots:
    void OnTimerTick();
    void SwitchTurn();

private:
    void CreateHexGrid(int size);
    void UpdateTileVisual(int q, int r, state tileState);
    void PlaySound(const QString& soundName);
    void ResetTimer();

    // Scene and visual
    QGraphicsScene* scene_;
    std::unordered_map<Coords, HexTile*, CoordsHash> hexTiles_;
    qreal hexRadius_;
    int boardSize_;

    // Game logic
    GameManager& gameManager_;
    state currentPlayer_;
    bool gameActive_;
    bool gamePaused_;

    // Timer
    QTimer* turnTimer_;
    int timeRemaining_;
    static constexpr int TURN_TIME_SECONDS = 10;

    // Sound effects - COMMENTED OUT (can be re-enabled later)
    // std::unique_ptr<QSoundEffect> placeTileSound_;
    // std::unique_ptr<QSoundEffect> winSound_;
    // std::unique_ptr<QSoundEffect> tickSound_;
    // bool soundsEnabled_;
};

#endif //HEX_HEXBOARD_HPP
