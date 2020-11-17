#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <code/include/Game.hpp>
#include <code/include/MapTile.hpp>

MapTile::MapTile(){}

void MapTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(0, 0, QPixmap(":/images/images/tileBackground.png"));
    painter->drawText(0, 30, "tile");
}

QRectF MapTile::boundingRect() const {
    int len = Game::game().tileWidth;
    return QRectF(0, 0, len, len);
}

