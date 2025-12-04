//
// Created by Stephen Donlin on 12/4/25.
//

#ifndef HEX_WINDOW_HPP
#define HEX_WINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>

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

    private:
        Ui::Window *ui;
        QGraphicsScene *scene;


};



#endif //HEX_WINDOW_HPP
