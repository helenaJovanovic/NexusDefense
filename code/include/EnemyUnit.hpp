#ifndef ENEMYUNIT_HPP
#define ENEMYUNIT_HPP

#include <code/include/Game.hpp>

#include <QGraphicsRectItem>
#include <QDebug>

class EnemyUnit : public QGraphicsRectItem {
public:
    EnemyUnit(QPointF spawnPos);

    ~EnemyUnit();

    //Current status of the unit
    bool isAlive;

    //Getters
    float getMaxHealth() const;
    float getCurrentHealth() const;
    float getMovementSpeed() const;

    //Methods for unit functionality
    void takeDamage(float damageAmount);

    //Methods for drawing the unit on the scene (from parent class QGraphicsItem)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    //Fields hard coded for now...
    float maxHealth = 500;
    float currentHealth = 500;

    float movementSpeed = 10;
    float attackDamage = 40;

};

#endif // ENEMYUNIT_HPP
