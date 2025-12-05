#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "gameManager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow {
    Q_OBJECT

public:
        Window(const QString& player1Name, const QString& player2Name, QWidget *parent = nullptr);
        ~Window();

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

        void setupGame();
        void updatePlayerDisplay();
        void formatTimerDisplay(int seconds);
        void resetTurnTimer();
        void passTurn();
};

#endif // WINDOW_H