//
// Created by Stephen Donlin on 12/4/25.
//

#include "Window.hpp"
#include "ui_Window.h"


#include <QGraphicsScene>

#include "hexTile.hpp"
#include "../headers/gameManager.hpp"
#include "../headers/utils.hpp"
#include "../headers/theme.hpp"
// hex items




Window::Window(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::Window)
{
    ui->setupUi(this);  // connects designer widgets to ui
    QGraphicsView *view = ui -> graphicsView; // access the view

    // set color
    view -> setBackgroundBrush(theme::SCENE_BACKGROUND);

    scene = new QGraphicsScene();
    // create a single hex
    //auto tile = new HexTile(0, 0, 20);
    //tile -> SetState(state::kBlack);

    int size = 11;
    qreal radius = 25.0;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            auto [q, r] = utils::offset_to_axial(row, col);
            auto* tile = new HexTile(q, r, radius);
            scene->addItem(tile);
        }
    }

    view -> setScene(scene); // assign the scene
    view->rotate(-30);
    ui->graphicsView->setScene(scene);
    //scene->addText("Hello Hex");
    //scene->addItem(tile);

    // init GameManager, build hex grid, add HexItem objects to scene, etc.
}

Window::~Window() {
    delete ui;
}
