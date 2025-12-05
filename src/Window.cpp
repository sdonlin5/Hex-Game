#include "../headers/Window.hpp"
#include "ui_Window.h"
#include <QMessageBox>

Window::Window(const QString& player1Name, const QString& player2Name, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
    , secondsRemaining(10)
    , player1Name_(player1Name)
    , player2Name_(player2Name)
    , currentPlayer_(state::kBlack)
{
    ui->setupUi(this);

    // Set fixed window size to prevent resizing
    setFixedSize(size());

    // Initialize turn timer (counts down from 10 seconds)
    turnTimer = new QTimer(this);
    connect(turnTimer, &QTimer::timeout, this, &Window::updateTurnTimer);

    // Connect resign button
    connect(ui->resignButton, &QPushButton::clicked, this, &Window::onResignClicked);

    // Setup game
    setupGame();

    // Start turn timer
    resetTurnTimer();
    turnTimer->start(1000); // Update every second
}

Window::~Window()
{
    delete ui;
}

void Window::setupGame()
{
    // Initialize game manager
    GameManager::GetInstance().SetUp(11);

    // Set initial player display
    currentPlayer_ = state::kBlack;
    updatePlayerDisplay();

    // Reset turn timer
    resetTurnTimer();
}

void Window::resetTurnTimer()
{
    secondsRemaining = 10;
    formatTimerDisplay(secondsRemaining);
}

void Window::updateTurnTimer()
{
    secondsRemaining--;
    formatTimerDisplay(secondsRemaining);

    // If time runs out, pass the turn
    if (secondsRemaining <= 0) {
        passTurn();
    }
}

void Window::passTurn()
{
    // Switch to the other player
    if (currentPlayer_ == state::kBlack) {
        currentPlayer_ = state::kGold;
    } else {
        currentPlayer_ = state::kBlack;
    }

    // Reset timer for next player
    resetTurnTimer();
    updatePlayerDisplay();
}

void Window::formatTimerDisplay(int seconds)
{
    QString timeText = QString("%1").arg(seconds, 2, 10, QChar('0'));

    // Change color to red when time is running out
    if (seconds <= 3) {
        ui->timerLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
    } else {
        ui->timerLabel->setStyleSheet("QLabel { color: black; font-weight: bold; }");
    }

    ui->timerLabel->setText(timeText + "s");
}

void Window::updatePlayerDisplay()
{
    QString playerName;
    QString colorText;

    if (currentPlayer_ == state::kBlack) {
        playerName = player1Name_;
        colorText = "Black";
    } else {
        playerName = player2Name_;
        colorText = "Gold";
    }

    ui->currentPlayerLabel->setText(QString("Current Player:\n%1\n(%2)").arg(playerName).arg(colorText));
}

void Window::onResignClicked()
{
    QMessageBox::StandardButton reply;

    QString playerName = (currentPlayer_ == state::kBlack) ? player1Name_ : player2Name_;

    reply = QMessageBox::question(this, "Resign Game",
                                   QString("%1, are you sure you want to resign?").arg(playerName),
                                   QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        turnTimer->stop();

        QString winnerName = (currentPlayer_ == state::kBlack) ? player2Name_ : player1Name_;
        QMessageBox::information(this, "Game Over",
                                QString("%1 wins by resignation!").arg(winnerName));

        // Reset or close window
        QMessageBox::StandardButton restart;
        restart = QMessageBox::question(this, "New Game",
                                        "Would you like to start a new game?",
                                        QMessageBox::Yes | QMessageBox::No);

        if (restart == QMessageBox::Yes) {
            setupGame();
            turnTimer->start(1000);
        } else {
            close();
        }
    }
}