//
// Created by Stephen Donlin on 12/4/25.
//

#include "Window.hpp"
#include "ui_Window.h"

#include <QGraphicsScene>
#include <QResizeEvent>

#include "hexTile.hpp"
#include "../headers/gameManager.hpp"
#include "../headers/utils.hpp"
#include "../headers/theme.hpp"

Window::Window(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::Window)
{
    ui->setupUi(this);
    QGraphicsView *view = ui->graphicsView;

    // Set background color
    view->setBackgroundBrush(theme::SCENE_BACKGROUND);
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::NoDrag);

    scene = new QGraphicsScene(this);

    // Create hex grid
    int size = 11;
    qreal radius = 35.0;  // Good visible size

    // Build the board in offset coordinates (creates rhombus)
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            auto [q, r] = utils::offset_to_axial(row, col);
            auto* tile = new HexTile(q, r, radius);
            scene->addItem(tile);
        }
    }

    // Set the scene
    view->setScene(scene);

    // Add margin and fit
    QRectF bounds = scene->itemsBoundingRect();
    bounds.adjust(-50, -50, 50, 50);
    scene->setSceneRect(bounds);

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

Window::~Window() {
    delete ui;
}

void Window::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    // Refit the view when window is resized
    if (scene && ui->graphicsView) {
        ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
}