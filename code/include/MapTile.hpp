#ifndef MAPTILE_HPP
#define MAPTILE_HPP

#include "Map.hpp"

#include <QGraphicsRectItem>

class MapTile: public QGraphicsItem {
public:
    MapTile(QString type, QPixmap& texture);

    //bool contains(const QPointF &point) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    // type of the MapTile tells us if it's buildable,
    // an enemy road or nexus / spawn point
    // TODO replace QString with enum
    QString type;
    bool isUnitSpawn = false;
    bool isNexus = false;
    QPixmap& texture;

    int getX();
    int getY();

    void setX(int);
    void setY(int);

    void setOccuppied();
    bool getOcuppied();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int xCoord,yCoord;
    bool occupied = false;
};

#endif // MAPTILE_HPP
