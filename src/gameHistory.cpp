#include "../headers/gameHistory.hpp"
#include <QDebug>

GameHistory::GameHistory() {
    //
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // If AppDataLocation
    if (dataPath.isEmpty()) {
        dataPath = ".";
    }

    // Ensure directory exists
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    historyFilePath_ = dataPath + "/hex_game_history.csv";

    EnsureFileExists();

    qDebug() << "Game history file:" << historyFilePath_;
}

void GameHistory::EnsureFileExists() {
    QFile file(historyFilePath_);

    // If file doesn't exist, create it with headers
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "DateTime,Player1,Player2,Winner,WinnerColor,GameDurationSeconds\n";
            file.close();
            qDebug() << "Created new game history file with headers";
        } else {
            qWarning() << "Could not create game history file:" << file.errorString();
        }
    }
}

QString GameHistory::GetColorString(state color) const {
    switch (color) {
        case state::kBlack:
            return "Black";
        case state::kGold:
            return "Gold";
        default:
            return "None";
    }
}

void GameHistory::RecordResult(const QString& player1Name,
                              const QString& player2Name,
                              const QString& winnerName,
                              state winnerColor,
                              int gameDurationSeconds) {
    QFile file(historyFilePath_);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        // Get current date/time
        QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Escape any commas in player names by wrapping in quotes
        QString p1 = player1Name.contains(',') ? "\"" + player1Name + "\"" : player1Name;
        QString p2 = player2Name.contains(',') ? "\"" + player2Name + "\"" : player2Name;
        QString winner = winnerName.contains(',') ? "\"" + winnerName + "\"" : winnerName;

        // Write the record
        out << dateTime << ","
            << p1 << ","
            << p2 << ","
            << winner << ","
            << GetColorString(winnerColor) << ","
            << gameDurationSeconds << "\n";

        file.close();

        qDebug() << "Recorded game:" << winnerName << "(" << GetColorString(winnerColor) << ") won";
    } else {
        qWarning() << "Could not open game history file for writing:" << file.errorString();
    }
}


