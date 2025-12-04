//
// Created by Stephen Donlin on 12/4/25.
//

#include "../headers/hexTile.hpp"
#include "../headers/hexTile.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <cmath>

#include "theme.hpp"

 HexTile::HexTile(int q, int r, qreal radius) : q_(q), r_(r) {

     // convert axial to pixel space
     qreal x = radius * std::sqrt(3.0) * (q + r / 2.0);
     qreal y = radius * 1.5 * r;

     setPolygon(MakeHexTile(x, y, radius));
     setPen(QPen(Qt::black));
     setBrush(Qt::NoBrush);

}

void HexTile::SetState(state s) {
     state_ = s;
     if (s == state::kBlack) {
         setBrush(theme::BLACK_TILE);
     } else if (s == state::kGold) {
         setBrush(theme::GOLD_TILE);
     } else {
         setBrush(theme::OPEN_TILE);
     }
 }


QPolygonF HexTile::MakeHexTile(qreal cx, qreal cy, qreal radius) {
     // Creates a hex tile with a top vertex orientation
     QPolygonF tile;
     for (int i = 0; i < 6; ++i) {
         qreal angle_deg = 60 * i - 30;
         qreal angle_rad = angle_deg * M_PI / 180.0;
         qreal x = cx + radius * std::cos(angle_rad);
         qreal y = cy + radius * std::sin(angle_rad);
         tile << QPointF(x, y);
     }
     return tile;
 }


