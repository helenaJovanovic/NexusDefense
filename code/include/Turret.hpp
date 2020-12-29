#ifndef TURRET_HPP
#define TURRET_HPP

class Tower;
//class Projectile;
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QDebug>
#include <QPointer>
#include <code/include/Tower.hpp>
#include <code/include/Projectile.hpp>
//class Tower
//{
//};

class Turret : public QObject,public QGraphicsItem
{
    Q_OBJECT
private:
//    friend class Tower;
    Sprite* sprite;
    QLineF direction;
    Tower* tower;
    QPointF barrel;
    QMediaPlayer* fireSound;

public:
    Turret(Tower* tower);
    ~Turret();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void rotateToTarget();
    void fire();
    QLineF getDirection() const;
    void setDirection(const QLineF &value);
};




#endif // TURRET_HPP
