#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <vector>
#include "gameManager.hpp"

class HexTile;

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow {
    Q_OBJECT

public:
        Window(const QString& player1Name, const QString& player2Name, QWidget *parent = nullptr);
        ~Window();

        void handleTileClick(int q, int r);

    private slots:
        void updateTurnTimer();
        void onResignClicked();

    private:
        Ui::Window *ui;
        QTimer *turnTimer;
        int secondsRemaining;
        QString player1Name_;
        QString player2Name_;
        state currentPlayer_;
        QGraphicsScene *scene_;
        std::vector<std::vector<HexTile*>> hexTiles_;
        int boardSize_;

        void setupGame();
        void updatePlayerDisplay();
        void formatTimerDisplay(int seconds);
        void resetTurnTimer();
        void passTurn();
        void setupBoard();
        void renderBoard();
        void checkGameOver();
        void showWinDialog(state winner);
};

#endif // WINDOW_H