#include <QApplication>
#include <QPushButton>

#include "headers/gameManager.hpp"

int main() {
    std::cout << "Starting Hex" << std::endl;
    GameManager *game = &GameManager::GetInstance();
    game -> SetUp();
 //   game -> PrintBoard();
}
