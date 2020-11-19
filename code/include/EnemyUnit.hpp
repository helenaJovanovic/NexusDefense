#ifndef ENEMYUNIT_HPP
#define ENEMYUNIT_HPP

#include <QDir>
#include <QGraphicsRectItem>
#include <code/include/Game.hpp>

class EnemyUnit : public QGraphicsRectItem {
public:
    bool isAlive = false;

    EnemyUnit();

    //~EnemyUnit();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // ENEMYUNIT_HPP
