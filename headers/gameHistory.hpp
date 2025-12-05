#ifndef HEX_GAMEHISTORY_HPP
#define HEX_GAMEHISTORY_HPP

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include "state.hpp"

class GameHistory {
    public:
        static GameHistory& GetInstance() {
            static GameHistory instance;
            return instance;
        }

        // Delete copy constructor and assignment operator
        GameHistory(const GameHistory&) = delete;
        GameHistory& operator=(const GameHistory&) = delete;

        // Record a game result
        void RecordResult(const QString& player1Name,
                        const QString& player2Name,
                        const QString& winnerName,
                        state winnerColor,
                        int gameDurationSeconds);

        // Get the path to the CSV file
        QString GetHistoryFilePath() const { return historyFilePath_; }

    private:
        GameHistory();

        void EnsureFileExists();
        QString GetColorString(state color) const;
        QString historyFilePath_;
};

#endif