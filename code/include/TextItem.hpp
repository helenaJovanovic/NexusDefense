#ifndef TEXTITEM_HPP
#define TEXTITEM_HPP

#include <QGraphicsTextItem>
#include <QPainter>

class TextItem : public QGraphicsTextItem
{
public:
    TextItem();

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TEXTITEM_HPP
