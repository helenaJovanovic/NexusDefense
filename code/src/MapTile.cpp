#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <code/include/Game.hpp>
#include <code/include/MapTile.hpp>
#include <QDebug>

MapTile::MapTile(){}

void MapTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(32, 32, QPixmap(":/images/images/tileBackground.png"));
}

QRectF MapTile::boundingRect() const {
    int len = Game::game().tileWidth;
    return QRectF(len/2, len/2, len, len);
}

