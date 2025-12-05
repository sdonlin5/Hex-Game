#ifndef HEX_HEXBOARD_HPP
#define HEX_HEXBOARD_HPP

#include <QGraphicsScene>
#include <QTimer>
#include <unordered_map>

#include "hexTile.hpp"
#include "gameManager.hpp"
#include "coords.hpp"


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

    // getters
    state GetCurrentPlayer() const { return currentPlayer_; }
    int GetTimeRemaining() const { return timeRemaining_; }
    bool IsGameActive() const { return gameActive_; }
    QRectF GetBoardBounds() const;

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

    // visuals
    QGraphicsScene* scene_;
    std::unordered_map<Coords, HexTile*, CoordsHash> hexTiles_;
    qreal hexRadius_;
    int boardSize_;

    // gameplay logic
    GameManager& gameManager_;
    state currentPlayer_;
    bool gameActive_;
    bool gamePaused_;

    // turn timer
    QTimer* turnTimer_;
    int timeRemaining_;
    static constexpr int TURN_TIME_SECONDS = 10;
};

#endif
