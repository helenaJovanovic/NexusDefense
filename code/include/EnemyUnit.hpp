#ifndef ENEMYUNIT_HPP
#define ENEMYUNIT_HPP

#include <code/include/Game.hpp>

#include <QGraphicsRectItem>
#include <QDebug>

class EnemyUnit : public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    //Creates an EnemyUnit object and places it on the scene @ spawnPoint
    EnemyUnit(QPointF spawnPoint);

    ~EnemyUnit();

    //Current status of the unit
    bool isAlive;

    //Getters
    float getMaxHealth() const;
    float getCurrentHealth() const;
    float getMovementSpeed() const;

    //Reduces the unit's healh by damageAmount and destroys it if currentHealth <= 0
    void takeDamage(float damageAmount);

    //Methods for drawing the unit on the scene (from parent class QGraphicsRectItem)
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
