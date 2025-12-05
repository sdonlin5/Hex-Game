
#include "start.hpp"
#include "ui_StartScreen.h"
#include <QMessageBox>

StartScreen::StartScreen(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::StartScreen),
      player1Name_("Player 1"),
      player2Name_("Player 2")
{
    ui->setupUi(this);

    // Set window title
    setWindowTitle("Hex Game - Start");

    // Set default names in the text fields
    ui->player1LineEdit->setText("Player 1");
    ui->player2LineEdit->setText("Player 2");

    // Select the text so user can start typing immediately
    ui->player1LineEdit->setFocus();
    ui->player1LineEdit->selectAll();

    // Connect start button
    connect(ui->startButton, &QPushButton::clicked, this, &StartScreen::OnStartClicked);
}

StartScreen::~StartScreen() {
    delete ui;
}

void StartScreen::OnStartClicked() {
    // Get player names from text fields
    player1Name_ = ui->player1LineEdit->text().trimmed();
    player2Name_ = ui->player2LineEdit->text().trimmed();

    // Validate names are not empty
    if (player1Name_.isEmpty()) {
        player1Name_ = "Player 1";
    }

    if (player2Name_.isEmpty()) {
        player2Name_ = "Player 2";
    }

    // Check if names are the same
    if (player1Name_ == player2Name_) {
        QMessageBox::warning(this, "Duplicate Names",
                           "Players must have different names!");
        return;
    }

    // Accept the dialog (closes with Accepted status)
    accept();
}
