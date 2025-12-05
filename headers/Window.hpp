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
        void updateTimer();
        void onResignClicked();

    private:
        Ui::Window *ui;
        QTimer *gameTimer;
        int elapsedSeconds;
        QString player1Name_;
        QString player2Name_;
        state currentPlayer_;

        void setupGame();
        void updatePlayerDisplay();
        void formatTimerDisplay(int seconds);
};

#endif // WINDOW_H