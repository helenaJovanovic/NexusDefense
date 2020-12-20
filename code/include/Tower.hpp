#ifndef TOWER_HPP
#define TOWER_HPP

class Turret;

#include <code/include/Game.hpp>
#include <QGraphicsRectItem>
#include <QDebug>
#include <code/include/MapTile.hpp>
#include <code/include/Map.hpp>
#include <QPointer>
#include <QMediaPlayer>
#include <code/include/EnemyUnit.hpp>
//#include <code/include/Projectile.hpp>
#include "Turret.hpp"

class Tower : public QObject,public QGraphicsItem
{
    Q_OBJECT
private:

    QGraphicsPolygonItem* attackArea;
    //damage dealt per attack
    float attackDamage=50;
    //number of attacks in 1 second
    float attackSpeed=1;
    MapTile* locationOnMap;//anchor tile if tower spans more than one
    //number of tiles
    int width;
    int height;
    EnemyUnit* target=nullptr;
    int numberOfTicks=0;
    Sprite* sprite;
    Turret* turret;
    QMediaPlayer* constructionSound;

public:
    //Creates a tower on specified map tile
    Tower(MapTile* tile,float attackRange,int width,int height,QString spriteName);
    Tower(int x,int y,float attackRange,int width,int height,QString spriteName);
    ~Tower();
    //check if current target is still in range
    bool currentTargetInRange();
    //Target an enemy unit
    void acquireTarget();
    //Attack if it has a target
    void attack();
    //get distance between tower and item
    double distanceTo(QGraphicsItem* item);
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    //getters
    float getAttackDamage() const;
    float getAttackSpeed() const;
    int getWidth() const;
    int getHeight() const;
    MapTile* getLocationOnMap() const;
    QGraphicsPolygonItem *getAttackArea() const;
    void acquireTargetAndAttack();


    void setTarget(EnemyUnit *value);

    Sprite *getSprite() const;

    EnemyUnit *getTarget() const;

public slots:
    //on timer tick
    void update();
};

#endif // TOWER_HPP
