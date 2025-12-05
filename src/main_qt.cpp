#include <QApplication>
#include "../headers/Window.hpp"
#include "../headers/start.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Show start screen to get player names
    StartScreen startScreen;
    
    // If user cancels (closes dialog), exit the application
    if (startScreen.exec() != QDialog::Accepted) {
        return 0;
    }
    
    // Get player names from start screen
    QString player1Name = startScreen.GetPlayer1Name();
    QString player2Name = startScreen.GetPlayer2Name();
    
    // Create and show main game window with player names
    Window window(player1Name, player2Name);
    window.show();

    return app.exec();
}
