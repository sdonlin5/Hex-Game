//
// Created by Stephen Donlin on 12/4/25.
//

#ifndef HEX_HEXTILE_HPP
#define HEX_HEXTILE_HPP

#include <QGraphicsPolygonItem>
#include <QBrush>
#include <QPen>
#include <memory>
#include "hex.hpp"
#include "coords.hpp"
#include "theme.hpp"

class HexBoard; // Forward declaration

class HexTile : public QGraphicsPolygonItem {
    public:
        HexTile(int q, int r, qreal radius, HexBoard* board = nullptr);

        int q() const { return q_; }
        int r() const { return r_; }

        void SetState(state color);
        state GetState() const { return state_; }

        void SetHighlight(bool highlight);
        void SetHover(bool hover);

    protected:
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    private:
        QPolygonF MakeHexTile(qreal cx, qreal cy, qreal radius);
        void UpdateColors();

        int q_;
        int r_;
        qreal radius_;
        state state_;
        bool highlighted_;
        bool hovered_;
        HexBoard* board_;
};

#endif //HEX_HEXTILE_HPP