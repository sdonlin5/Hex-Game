//
// Created by Stephen Donlin on 12/4/25.
//

#ifndef HEX_WINDOW_HPP
#define HEX_WINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include "hexBoard.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow {
    Q_OBJECT

public:
        explicit Window(QWidget* parent = nullptr);
        ~Window();

    protected:
        void resizeEvent(QResizeEvent* event) override;

    private slots:
        void OnStartGame();
        void OnResetGame();
        void OnPauseGame();
        void OnTurnChanged(state player);
        void OnTimerTick(int seconds);
        void OnGameOver(state winner);

    private:
        void SetupUI();
        void ConnectSignals();

        Ui::Window *ui;
        QGraphicsScene *scene_;
        HexBoard *hexBoard_;
        bool gamePaused_;
};

#endif //HEX_WINDOW_HPP