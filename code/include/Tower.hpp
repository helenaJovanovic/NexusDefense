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
#include <code/include/TowerLoader.hpp>
#include <code/include/EnemyUnit.hpp>
//#include <code/include/Projectile.hpp>
#include "Turret.hpp"

class Tower : public QObject,public QGraphicsItem
{
    Q_OBJECT
private:

    QGraphicsPolygonItem* attackArea;
    //damage dealt per attack
//    float attackDamage;
    //number of timer ticks needed for an attack
//    float attackSpeed;
    MapTile* locationOnMap;//anchor tile if tower spans more than one
    //number of tiles
//    int width;
//    int height;
    EnemyUnit* target=nullptr;
    int numberOfTicks=0;
    Sprite* sprite;
    Turret* turret;
    QMediaPlayer* constructionSound;


    TowerLoader* attributes;


    //fields are parsed by TowerLoader from json
//    QString name;
//    //range is saved as attackArea
//    //width(length) in tiles
//    int width;
//    //height in tiles
//    int height;
//    //damage per hit
//    float attackDamage;
//    //number of timer ticks for each attack
//    float attackSpeed;



public:
    //Creates a tower on specified map tile
    Tower(MapTile* tile,QString towerType);
    Tower(int x, int y, QString towerType);
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
    MapTile* getLocationOnMap() const;
    QGraphicsPolygonItem *getAttackArea() const;
    void acquireTargetAndAttack();


    void setTarget(EnemyUnit *value);

    Sprite *getSprite() const;

    EnemyUnit *getTarget() const;

    TowerLoader* getAttributes() const;

    void upgrade();

public slots:
    //on timer tick
    void update();
    void onConstructionFinished();
};

#endif // TOWER_HPP
