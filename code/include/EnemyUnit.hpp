#ifndef ENEMYUNIT_HPP
#define ENEMYUNIT_HPP

#include <code/include/Game.hpp>
#include <code/include/Sprite.hpp>

#include <QGraphicsRectItem>
#include <QDebug>

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
    int frameNumber = 0;
    int deathFrameNumber = 0;
    int timeElapsed;
    bool deathPhase = false;

    Sprite* unitSprite;
    Sprite* explosionSprite;
    QMap<QString, QVector<Sprite::frame>> unitSpriteMap;
    QMap<QString, QVector<Sprite::frame>> explosionSpriteMap;

    QPoint currentOriginPoint;
    QRect currentOriginRect;
    QString currentSpritesheet;

private slots:
    void move();
    void animate();
    void boom();

};

#endif // ENEMYUNIT_HPP
