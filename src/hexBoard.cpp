//
// Created by Stephen Donlin on 12/4/25.
//

#include "../headers/hexBoard.hpp"
#include "../headers/utils.hpp"
#include <QDebug>
#include <QUrl>

HexBoard::HexBoard(QGraphicsScene* scene, int boardSize, qreal hexRadius, QObject* parent)
    : QObject(parent)
    , scene_(scene)
    , hexRadius_(hexRadius)
    , boardSize_(boardSize)
    , gameManager_(GameManager::GetInstance())
    , currentPlayer_(state::kBlack)
    , gameActive_(false)
    , gamePaused_(false)
    , timeRemaining_(TURN_TIME_SECONDS)
    , soundsEnabled_(false)  // Set to true if you add sound files
{
    // Initialize timer
    turnTimer_ = new QTimer(this);
    connect(turnTimer_, &QTimer::timeout, this, &HexBoard::OnTimerTick);

    // Initialize sound effects (optional - only if sound files exist)
    if (soundsEnabled_) {
        placeTileSound_ = std::make_unique<QSoundEffect>();
        placeTileSound_->setSource(QUrl::fromLocalFile("resources/sounds/place_tile.wav"));
        placeTileSound_->setVolume(0.5);

        winSound_ = std::make_unique<QSoundEffect>();
        winSound_->setSource(QUrl::fromLocalFile("resources/sounds/win.wav"));
        winSound_->setVolume(0.7);

        tickSound_ = std::make_unique<QSoundEffect>();
        tickSound_->setSource(QUrl::fromLocalFile("resources/sounds/tick.wav"));
        tickSound_->setVolume(0.3);
    }

    InitializeBoard(boardSize);
}

HexBoard::~HexBoard() {
    ClearBoard();
}

void HexBoard::InitializeBoard(int size) {
    boardSize_ = size;
    ClearBoard();

    // Initialize game manager with board size
    gameManager_.SetUp(size);

    CreateHexGrid(size);

    currentPlayer_ = state::kBlack;
    gameActive_ = false;
    gamePaused_ = false;
    timeRemaining_ = TURN_TIME_SECONDS;
}

void HexBoard::CreateHexGrid(int size) {
    // Create visual hex tiles
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            auto [q, r] = utils::offset_to_axial(row, col);

            HexTile* hexTile = new HexTile(q, r, hexRadius_, this);
            scene_->addItem(hexTile);

            hexTiles_[Coords{q, r}] = hexTile;
        }
    }

    qDebug() << "Created" << hexTiles_.size() << "hex tiles";
}

void HexBoard::ClearBoard() {
    // Remove all tiles from scene
    for (auto& [coords, tile] : hexTiles_) {
        scene_->removeItem(tile);
        delete tile;
    }
    hexTiles_.clear();
}

void HexBoard::ResetBoard() {
    InitializeBoard(boardSize_);
    turnTimer_->stop();
    emit TurnChanged(currentPlayer_);
    emit TimerTick(timeRemaining_);
}

QRectF HexBoard::GetBoardBounds() const {
    if (scene_) {
        QRectF bounds = scene_->itemsBoundingRect();
        bounds.adjust(-50, -50, 50, 50);  // Add margin
        return bounds;
    }
    return QRectF();
}

void HexBoard::OnTileClicked(int q, int r) {
    if (!gameActive_ || gamePaused_) {
        qDebug() << "Game not active, ignoring click";
        return;
    }

    qDebug() << "Tile clicked:" << q << r << "by player" << (int)currentPlayer_;

    // Attempt to play move through GameManager
    bool validMove = gameManager_.PlayMove(q, r, currentPlayer_);

    if (validMove) {
        // Update visual representation
        UpdateTileVisual(q, r, currentPlayer_);

        PlaySound("place_tile");

        emit MoveCompleted(currentPlayer_, true);
        emit TileClicked(q, r);

        // Check for win
        if (gameManager_.CheckWin(currentPlayer_)) {
            gameActive_ = false;
            turnTimer_->stop();
            PlaySound("win");
            qDebug() << "Player" << (int)currentPlayer_ << "wins!";
            emit GameOver(currentPlayer_);
        } else {
            // Switch to next player
            SwitchTurn();
        }
    } else {
        qDebug() << "Invalid move at" << q << r;
        emit MoveCompleted(currentPlayer_, false);
    }
}

void HexBoard::UpdateTileVisual(int q, int r, state tileState) {
    Coords coords{q, r};
    auto it = hexTiles_.find(coords);

    if (it != hexTiles_.end()) {
        it->second->SetState(tileState);
    } else {
        qWarning() << "Could not find tile at" << q << r;
    }
}

void HexBoard::SwitchTurn() {
    currentPlayer_ = (currentPlayer_ == state::kBlack) ? state::kGold : state::kBlack;
    ResetTimer();
    qDebug() << "Turn switched to player" << (int)currentPlayer_;
    emit TurnChanged(currentPlayer_);
}

void HexBoard::ResetTimer() {
    timeRemaining_ = TURN_TIME_SECONDS;
    emit TimerTick(timeRemaining_);
}

void HexBoard::OnTimerTick() {
    if (gamePaused_) return;

    timeRemaining_--;
    emit TimerTick(timeRemaining_);

    if (timeRemaining_ <= 3 && timeRemaining_ > 0) {
        PlaySound("tick");
    }

    if (timeRemaining_ <= 0) {
        qDebug() << "Time's up for player" << (int)currentPlayer_;
        SwitchTurn();
    }
}

void HexBoard::StartGame() {
    gameActive_ = true;
    gamePaused_ = false;
    currentPlayer_ = state::kBlack;
    ResetTimer();
    turnTimer_->start(1000);  // 1 second intervals
    qDebug() << "Game started";
    emit TurnChanged(currentPlayer_);
}

void HexBoard::PauseGame() {
    gamePaused_ = true;
    turnTimer_->stop();
    qDebug() << "Game paused";
}

void HexBoard::ResumeGame() {
    if (gameActive_) {
        gamePaused_ = false;
        turnTimer_->start(1000);
        qDebug() << "Game resumed";
    }
}

void HexBoard::PlaySound(const QString& soundName) {
    if (!soundsEnabled_) return;

    if (soundName == "place_tile" && placeTileSound_) {
        placeTileSound_->play();
    } else if (soundName == "win" && winSound_) {
        winSound_->play();
    } else if (soundName == "tick" && tickSound_) {
        tickSound_->play();
    }
}