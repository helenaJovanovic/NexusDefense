#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <QGraphicsItem>
#include <QDebug>
#include <QPointer>
#include <code/include/EnemyUnit.hpp>


class Projectile : public QObject,public QGraphicsItem
{
    Q_OBJECT
private:
    float damage;
    float speed;//delay factor
    float blastRadius;
    QPointer<EnemyUnit> target;
    QLineF direction;
    float length;
    float height;
    QString imagePath;
public:
    Projectile(float blastRadius,float length,float height,QString imagePath,float damage,float speed,QPointer<EnemyUnit> target,QPointF startPosition);
    ~Projectile();


    float getDamage() const;
    float getSpeed() const;
    QPointer<EnemyUnit> getTarget() const;

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    //if it reaches the target , destroy the projectile and deal damage
    //return true if projectile destroyed
    bool impact();
    //homing projectile - direction always towards unit
    //move projectile
    void moveToTarget();
    //rotate towards target(changes direction)
    void rotateToTarget();
    //check if target alive,destroy the projectile if not
    bool targetAlive();

public slots:
    //move towards target on each tick
    void update();
};

#endif // PROJECTILE_HPP
