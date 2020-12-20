#ifndef TURRET_HPP
#define TURRET_HPP

class Tower;
//class Projectile;
#include <QGraphicsItem>
#include <QDebug>
#include <QPointer>
#include <QMediaPlayer>
#include <code/include/Tower.hpp>
#include <code/include/Projectile.hpp>
//class Tower
//{
//};

class Turret : public QObject,public QGraphicsItem
{
    Q_OBJECT
private:
    friend class Tower;
    Sprite* sprite;
    QLineF direction;
    QMediaPlayer* fireSound;
    Tower* tower;
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
