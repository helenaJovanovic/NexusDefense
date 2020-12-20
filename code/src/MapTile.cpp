#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <code/include/Game.hpp>
#include <code/include/MapTile.hpp>
#include <QGraphicsSceneMouseEvent>

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

    //Uncomment to see which type of tile it is
    //painter->drawText(8, 15, typeString);
}

QRectF MapTile::boundingRect() const {
    int len = Game::game().tileWidth;
    return QRectF(0, 0, len, len);
}

void MapTile::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        if(type == "T" || type == "TE"){
            qDebug() << "Tile is tower tile";
        }
        qDebug() << "clicked at maptile pos: " << getX() << ", " << getY();

    }

    QGraphicsItem::mousePressEvent(event);
}


int MapTile::getX() {
    return xCoord;
}

int MapTile::getY() {
    return yCoord;
}

void MapTile::setX(int x) {
    xCoord = x;
}

void MapTile::setY(int y) {
    yCoord = y;
}

