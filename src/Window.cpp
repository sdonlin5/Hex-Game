#include "../headers/Window.hpp"
#include "../headers/hexTile.hpp"
#include "../headers/utils.hpp"
#include "../headers/gameHistory.hpp"
#include "ui_Window.h"
#include <QMessageBox>
#include <QGraphicsTextItem>
#include <cmath>

Window::Window(const QString& player1Name, const QString& player2Name, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
    , secondsRemaining(10)
    , player1Name_(player1Name)
    , player2Name_(player2Name)
    , currentPlayer_(state::kBlack)
    , scene_(nullptr)
    , boardSize_(11)
{
    ui->setupUi(this);

    // Set fixed window size to prevent resizing
    setFixedSize(size());

    // Setup graphics scene
    scene_ = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene_);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // Initialize turn timer (counts down from 10 seconds)
    turnTimer = new QTimer(this);
    connect(turnTimer, &QTimer::timeout, this, &Window::updateTurnTimer);

    // Connect resign button
    connect(ui->resignButton, &QPushButton::clicked, this, &Window::onResignClicked);

    // Setup game
    setupGame();

    // Start turn timer
    resetTurnTimer();
    turnTimer->start(1000);
}

Window::~Window()
{
    delete ui;
}

void Window::setupGame()
{
    // Initialize game manager
    GameManager::GetInstance().SetUp(boardSize_);

    // Setup the board visualization
    setupBoard();

    // Set initial player display
    currentPlayer_ = state::kBlack;
    updatePlayerDisplay();

    // Reset turn timer
    resetTurnTimer();

    // Start game timer for duration tracking
    gameTimer_.start();
}

void Window::setupBoard()
{
    scene_->clear();
    hexTiles_.clear();
    hexTiles_.resize(boardSize_, std::vector<HexTile*>(boardSize_, nullptr));

    renderBoard();
}

void Window::renderBoard()
{
    const qreal hexSize = 25.0;
    const qreal xSpacing = hexSize * 1.73;  // sqrt(3) * hexSize
    const qreal ySpacing = hexSize * 1.5;

    // Center offset
    const qreal centerX = 350;
    const qreal centerY = 325;

    // Draw board edges (colored borders)
    // Top and bottom edges - Black
    QPen blackPen(Qt::black, 4);
    scene_->addLine(0, -10, 700, -10, blackPen);
    scene_->addLine(0, 660, 700, 660, blackPen);

    // Left and right edges - Gold
    QPen goldPen(QColor(255, 215, 0), 4);
    scene_->addLine(-10, 0, -10, 650, goldPen);
    scene_->addLine(710, 0, 710, 650, goldPen);

    // Create hex tiles
    for (int row = 0; row < boardSize_; ++row) {
        for (int col = 0; col < boardSize_; ++col) {
            // Convert to axial coordinates
            auto [q, r] = utils::offset_to_axial(row, col);

            // Calculate position
            qreal xPos = centerX + (col - boardSize_/2.0) * xSpacing + (row % 2) * (xSpacing / 2.0);
            qreal yPos = centerY + (row - boardSize_/2.0) * ySpacing;

            // Create hex tile
            HexTile* hexTile = new HexTile(q, r, hexSize, this);
            hexTile->setPos(xPos, yPos);
            scene_->addItem(hexTile);

            hexTiles_[row][col] = hexTile;
        }
    }

    // Add labels
    QGraphicsTextItem* blackLabel = scene_->addText("Black: Top ↔ Bottom");
    blackLabel->setDefaultTextColor(Qt::black);
    blackLabel->setPos(250, -40);

    QGraphicsTextItem* goldLabel = scene_->addText("Gold: Left ↔ Right");
    goldLabel->setDefaultTextColor(QColor(255, 215, 0));
    goldLabel->setPos(250, 665);
}

void Window::handleTileClick(int q, int r)
{
    // Attempt to play the move
    if (GameManager::GetInstance().PlayMove(q, r, currentPlayer_)) {
        // Update tile appearance
        auto [row, col] = utils::axial_to_offset(q, r);
        hexTiles_[row][col]->setState(currentPlayer_);

        // Check for win
        checkGameOver();

        if (!GameManager::GetInstance().IsGameOver()) {
            // Switch player and reset timer
            passTurn();
        }
    }
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
        ui->timerLabel->setStyleSheet("QLabel { color: red; font-weight: bold; font-size: 24pt; }");
    } else {
        ui->timerLabel->setStyleSheet("QLabel { color: black; font-weight: bold; font-size: 24pt; }");
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

void Window::checkGameOver()
{
    if (GameManager::GetInstance().IsGameOver()) {
        turnTimer->stop();
        state winner = GameManager::GetInstance().GetWinner();
        recordGameResult(winner);
        showWinDialog(winner);
    }
}

void Window::recordGameResult(state winner)
{
    // Get winner name
    QString winnerName = (winner == state::kBlack) ? player1Name_ : player2Name_;

    // Calculate game duration in seconds
    int durationSeconds = static_cast<int>(gameTimer_.elapsed() / 1000);

    // Record to CSV
    GameHistory::GetInstance().RecordResult(
        player1Name_,
        player2Name_,
        winnerName,
        winner,
        durationSeconds
    );
}

void Window::showWinDialog(state winner)
{
    QString winnerName = (winner == state::kBlack) ? player1Name_ : player2Name_;
    QString winnerColor = (winner == state::kBlack) ? "Black" : "Gold";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game Over!");
    msgBox.setText(QString("%1 (%2) wins!").arg(winnerName).arg(winnerColor));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    // Ask for new game
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

void Window::onResignClicked()
{
    QMessageBox::StandardButton reply;

    QString playerName = (currentPlayer_ == state::kBlack) ? player1Name_ : player2Name_;

    reply = QMessageBox::question(this, "Resign Game",
                                   QString("%1, are you sure you want to resign?").arg(playerName),
                                   QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        turnTimer->stop();

        // Winner is the other player
        state winner = (currentPlayer_ == state::kBlack) ? state::kGold : state::kBlack;

        // Record the resignation as a game result
        recordGameResult(winner);

        showWinDialog(winner);
    }
}