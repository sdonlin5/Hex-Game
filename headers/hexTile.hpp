#ifndef HEXTILE_HPP
#define HEXTILE_HPP

#include <QGraphicsPolygonItem>
#include <QBrush>
#include <QPen>
#include "state.hpp"
#include "coords.hpp"

// forward declaration

class Window;

class HexTile : public QGraphicsPolygonItem {
    public:
        HexTile(int q, int r, qreal size, Window* window);

        void setState(state newState);
        state getState() const { return state_; }
        int getQ() const { return q_; }
        int getR() const { return r_; }

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    private:
        int q_;
        int r_;
        state state_;
        Window* window_;
        QBrush defaultBrush_;

        void updateAppearance();
};

#endif //
