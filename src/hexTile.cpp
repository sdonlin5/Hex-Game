#include "../headers/hexTile.hpp"
#include "../headers/Window.hpp"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

HexTile::HexTile(int q, int r, qreal size, Window* window)
    : q_(q), r_(r), state_(state::kNone), window_(window)
{
    //  hexagon polygon
    QPolygonF hexagon;
    for (int i = 0; i < 6; ++i) {
        qreal angle = M_PI / 3.0 * i;
        qreal x = size * cos(angle);
        qreal y = size * sin(angle);
        hexagon << QPointF(x, y);
    }

    setPolygon(hexagon);

    //
    defaultBrush_ = QBrush(QColor(220, 220, 220));
    setBrush(defaultBrush_);
    setPen(QPen(Qt::black, 2));

    // Enable hover and click events
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void HexTile::setState(state newState)
{
    state_ = newState;
    updateAppearance();
}

void HexTile::updateAppearance()
{
    switch (state_) {
        case state::kBlack:
            setBrush(QBrush(QColor(30, 30, 30)));
            break;
        case state::kGold:
            setBrush(QBrush(QColor(255, 215, 0)));
            break;
        case state::kNone:
            setBrush(defaultBrush_);
            break;
    }
}

void HexTile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && state_ == state::kNone) {
        window_->handleTileClick(q_, r_);
    }
    QGraphicsPolygonItem::mousePressEvent(event);
}

void HexTile::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    if (state_ == state::kNone) {
        setBrush(QBrush(QColor(180, 180, 200)));
    }
    QGraphicsPolygonItem::hoverEnterEvent(event);
}

void HexTile::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    if (state_ == state::kNone) {
        setBrush(defaultBrush_);
    }
    QGraphicsPolygonItem::hoverLeaveEvent(event);
}
