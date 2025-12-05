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
    , turnTimer_(nullptr)
{
    // Initialize timer
    turnTimer_ = new QTimer(this);
    connect(turnTimer_, &QTimer::timeout, this, &HexBoard::OnTimerTick);

    // Sound Effects -
    // soundsEnabled_ = false;

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
    // Create creates tiles - window creates own tiles

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            auto [q, r] = utils::offset_to_axial(row, col);
        }
    }

    qDebug() << "HexBoard: Grid initialized for size" << size;
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
    emit TurnChanged(static_cast<int>(currentPlayer_));
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

        emit MoveCompleted(static_cast<int>(currentPlayer_), true);
        emit TileClicked(q, r);

        // Check for win
        if (gameManager_.CheckWin(currentPlayer_)) {
            gameActive_ = false;
            turnTimer_->stop();
            qDebug() << "Player" << (int)currentPlayer_ << "wins!";
            emit GameOver(static_cast<int>(currentPlayer_));
        } else {
            // Switch to next player
            SwitchTurn();
        }
    } else {
        qDebug() << "Invalid move at" << q << r;
        emit MoveCompleted(static_cast<int>(currentPlayer_), false);
    }
}

void HexBoard::UpdateTileVisual(int q, int r, state tileState) {
    Coords coords{q, r};
    auto it = hexTiles_.find(coords);

    if (it != hexTiles_.end()) {
        it->second->setState(tileState);
    } else {
        qWarning() << "Could not find tile at" << q << r;
    }
}

void HexBoard::SwitchTurn() {
    currentPlayer_ = (currentPlayer_ == state::kBlack) ? state::kGold : state::kBlack;
    ResetTimer();
    qDebug() << "Turn switched to player" << (int)currentPlayer_;
    emit TurnChanged(static_cast<int>(currentPlayer_));
}

void HexBoard::ResetTimer() {
    timeRemaining_ = TURN_TIME_SECONDS;
    emit TimerTick(timeRemaining_);
}

void HexBoard::OnTimerTick() {
    if (gamePaused_) return;

    timeRemaining_--;
    emit TimerTick(timeRemaining_);

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
    emit TurnChanged(static_cast<int>(currentPlayer_));
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
    // Sound effects disabled - can be re-enabled later
    Q_UNUSED(soundName);
}
