#ifndef MAPTILE_HPP
#define MAPTILE_HPP

#include <QGraphicsRectItem>

class MapTile: public QGraphicsRectItem {
public:
    MapTile();

    //bool contains(const QPointF &point) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // MAPTILE_HPP
