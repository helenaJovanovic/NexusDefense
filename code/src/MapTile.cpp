#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <code/include/Game.hpp>
#include <code/include/MapTile.hpp>


MapTile::MapTile(QString type, QPixmap& texture)
    : type(type), texture(texture)
{}

void MapTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    QString typeString = type;

    if(isNexus)
        typeString = QString("NEX");
    if(isUnitSpawn)
        typeString = QString("SP");

    painter->drawPixmap(0, 0, texture);


    painter->drawText(8, 15, typeString);
}

QRectF MapTile::boundingRect() const {
    int len = Game::game().tileWidth;
    return QRectF(0, 0, len, len);
}

