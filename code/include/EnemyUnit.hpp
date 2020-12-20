#ifndef ENEMYUNIT_HPP
#define ENEMYUNIT_HPP

#include <code/include/Game.hpp>
#include <code/include/Sprite.hpp>

#include <QGraphicsRectItem>
#include <QDebug>
#include <QMediaPlayer>

class EnemyUnit : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    //Creates an EnemyUnit object and places it on the scene @ spawnPoint
    EnemyUnit(MapTile* spawnPoint, QString spriteName, int movementDelay);

    ~EnemyUnit();

    //Current status of the unit
    bool isAlive;

    //Getters
    float getMaxHealth() const;
    float getCurrentHealth() const;
    float getMovementDelay() const;

    //Setters
    void setMovementDelay(int movementDelay);

    //Reduces the unit's healh by damageAmount and destroys it if currentHealth <= 0
    void takeDamage(float damageAmount);

    //Methods for drawing the unit on the scene (from parent class QGraphicsRectItem)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    //Fields hard coded for now...
    float maxHealth = 500;
    float currentHealth = 500;

    float movementDelay = 2;
    float attackDamage = 40;

    //Ticks
    int numOfTicks = 0;

    bool stopMovement = false;

    //Moving directions
    QVector<QPointF> turnPoints;
    QVector<unsigned> turnDirections;

    int currentDirectionIndex;
    int currentDirection;
    int nextTurnPointIndex;
    int numOfTurns;
    int frameNumber;
    int timeElapsed;

    Sprite* sprite;
    QMap<QString, QVector<Sprite::frame>> spriteMap;

    QPoint currentOriginPoint;
    QRect currentOriginRect;
    QMediaPlayer *dyingSound;

private slots:
    void move();
    void animate();

};

#endif // ENEMYUNIT_HPP
