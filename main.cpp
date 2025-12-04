//
// Created by Stephen Donlin on 12/4/25.
//
#include <QApplication>
#include "Window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Window w;
    w.show();

    return app.exec();
}