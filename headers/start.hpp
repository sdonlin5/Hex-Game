//
// Created by Stephen Donlin on 12/4/25.
//

#ifndef HEX_STARTSCREEN_HPP
#define HEX_STARTSCREEN_HPP

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
    class StartScreen;
}
QT_END_NAMESPACE

class StartScreen : public QDialog {
    Q_OBJECT

public:
        explicit StartScreen(QWidget* parent = nullptr);
        ~StartScreen();

        QString GetPlayer1Name() const { return player1Name_; }
        QString GetPlayer2Name() const { return player2Name_; }

    private slots:
        void OnStartClicked();

    private:
        Ui::StartScreen *ui;
        QString player1Name_;
        QString player2Name_;
};

#endif //HEX_STARTSCREEN_HPP