#ifndef HEX_HEXTILE_HPP
#define HEX_HEXTILE_HPP

#include <QGraphicsPolygonItem>
#include <QBrush>
#include <QPen>
#include <memory>
#include "hex.hpp"
#include "coords.hpp"
#include "theme.hpp"

class HexTile : public QGraphicsPolygonItem {
    public:
        HexTile(int q, int r, qreal radius);

        int q() const { return q_; }
        int r() const { return r_; }

        void SetState(state color);
        //state state() const { return state_; }

        QPolygonF MakeHexTile(qreal cx, qreal cy, qreal radius);

    protected:
        //void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    private:
        int q_;
        int r_;
        enum state state_ { state::kNone };
};

#endif //HEX_HEXTILE_H
