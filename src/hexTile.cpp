//
// Created by Stephen Donlin on 12/4/25.
//

#include "../headers/hexTile.hpp"
#include "../headers/hexBoard.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <cmath>
#include "theme.hpp"
#include "../headers/utils.hpp"

HexTile::HexTile(int q, int r, qreal radius, HexBoard* board)
    : q_(q), r_(r), radius_(radius), state_(state::kNone),
      highlighted_(false), hovered_(false), board_(board)
{
    // Convert axial back to offset for positioning
    auto [row, col] = utils::axial_to_offset(q, r);

    // Calculate hex dimensions for pointy-top orientation
    qreal width = std::sqrt(3.0) * radius;
    qreal height = 2.0 * radius;

    // Calculate position
    qreal x = col * width + (row & 1) * (width / 2.0);
    qreal y = row * height * 0.75;

    // Create polygon centered at (0, 0)
    setPolygon(MakeHexTile(0, 0, radius));

    // Set the item's position in the scene
    setPos(x, y);

    setPen(QPen(theme::TILE_BORDER, 2));
    setBrush(theme::OPEN_TILE);

    setAcceptHoverEvents(true);
}

void HexTile::SetState(state s) {
    state_ = s;
    UpdateColors();
}

void HexTile::SetHighlight(bool highlight) {
    highlighted_ = highlight;
    UpdateColors();
}

void HexTile::SetHover(bool hover) {
    hovered_ = hover;
    UpdateColors();
}

void HexTile::UpdateColors() {
    QColor fillColor;

    if (state_ == state::kBlack) {
        fillColor = theme::BLACK_TILE;
    } else if (state_ == state::kGold) {
        fillColor = theme::GOLD_TILE;
    } else {
        // Empty tile
        if (highlighted_) {
            fillColor = theme::TILE_HIGHLIGHT;
        } else if (hovered_) {
            fillColor = theme::OPEN_TILE.lighter(110);
        } else {
            fillColor = theme::OPEN_TILE;
        }
    }

    setBrush(fillColor);
}

void HexTile::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    if (state_ == state::kNone) {
        SetHover(true);
    }
    QGraphicsPolygonItem::hoverEnterEvent(event);
}

void HexTile::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    SetHover(false);
    QGraphicsPolygonItem::hoverLeaveEvent(event);
}

void HexTile::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton && board_) {
        board_->OnTileClicked(q_, r_);
    }
    QGraphicsPolygonItem::mousePressEvent(event);
}

QPolygonF HexTile::MakeHexTile(qreal cx, qreal cy, qreal radius) {
    // Creates a hex tile with pointy-top orientation centered at (cx, cy)
    QPolygonF tile;
    for (int i = 0; i < 6; ++i) {
        qreal angle_deg = 60 * i - 30;  // -30 for pointy-top
        qreal angle_rad = angle_deg * M_PI / 180.0;
        qreal x = cx + radius * std::cos(angle_rad);
        qreal y = cy + radius * std::sin(angle_rad);
        tile << QPointF(x, y);
    }
    return tile;
}