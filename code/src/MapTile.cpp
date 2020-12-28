#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <code/include/Game.hpp>
#include <code/include/MapTile.hpp>
#include <QGraphicsSceneMouseEvent>
#include <code/include/Tower.hpp>
//check this later

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
        if((type == "T" || type == "TE") && occupied == false){

            //TODO ??
            //You should get better guns based on the level, time elapsed
            //And more units appearing

            //for now
            //int level = 0;

            switch (Game::game().towerSelected) {
            case 0:
                if(Game::game().gold->getGold() >= 100){
                    new Tower(this, "mg");
                };
                break;
            case 1:
                if(Game::game().gold->getGold() >= 150){
                    new Tower(this, "cannon");
                };
                break;
            case 2:
                if(Game::game().gold->getGold() >= 200){
                    new Tower(this, "missile");
                };
                break;
            case 3: new Tower(this, "mg"); break;
            default: break;

            }

            occupied = true;
            Game::game().towerSelected = -1;

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

void MapTile::setOccuppied(){
    occupied = true;
}

bool MapTile::getOcuppied(){
    return occupied;
}

