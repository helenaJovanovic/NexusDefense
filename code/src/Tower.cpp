#include <code/include/Tower.hpp>
#include <cmath>




void Tower::setTarget(EnemyUnit *value)
{
    target = value;
}

Sprite *Tower::getSprite() const
{
    return sprite;
}

EnemyUnit *Tower::getTarget() const
{
    return target;
}

TowerLoader *Tower::getAttributes() const
{
    return attributes;
}

void Tower::upgrade()
{
    float level=attributes->getParameters()["level"];
    QString towerID=attributes->getName()["id"];
    if(level>=2)
        return;
    level++;
    delete attributes;
    attributes=new TowerLoader(towerID,level);
    float turretCenterX=
            this->getAttributes()->getParameters()["turretCenterPercentageX"]/100
            *
            this->getAttributes()->getParameters()["turretLength"];
    float turretCenterY=
            this->getAttributes()->getParameters()["turretCenterPercentageY"]/100
            *
            this->getAttributes()->getParameters()["turretHeight"];
    turret->setPos(this->pos()+QPoint(Game::game().tileWidth/2-turretCenterX,Game::game().tileWidth/2-turretCenterY));
    turret->setTransformOriginPoint(turretCenterX,turretCenterY);
//    qDebug()<<turretCenterX<<" - "<<turretCenterY<<"\n";
}

Tower::Tower(MapTile* tile,QString towerType)
    : locationOnMap(tile)
{
    attributes=new TowerLoader(towerType);
    float width=attributes->getParameters()["tileWidth"];
    float height=attributes->getParameters()["tileHeight"];
    float attackRange=attributes->getParameters()["range"];

//    this->setPos(this->locationOnMap->pos());
    this->setPos(this->locationOnMap->pos());
    QVector<QPointF> rangeOctagonPoints;
    QPointF towerCenter((width*Game::game().tileWidth)/2,(height*Game::game().tileWidth)/2);
    //octagon points,one on each 45 degrees
    float angleDegrees=0;
    for (int i = 0; i < 8; i++) {
        float angleRads=angleDegrees*M_PI/180.0;
        rangeOctagonPoints << QPoint(towerCenter.x()+attackRange*cos(angleRads),towerCenter.y()+attackRange*sin(angleRads));
        angleDegrees+=45;
    }
    attackArea=new QGraphicsPolygonItem(QPolygonF(rangeOctagonPoints),this);
//    attackArea->setPos(towerCenter.x(),towerCenter.y());
    attackArea->setOpacity(0);
//    Game::game().scene->addItem(attackArea);
    turret=new Turret(this);
    Game::game().scene->addItem(this);
    Game::game().scene->addItem(turret);
    connect(Game::game().gameTimer, SIGNAL(timeout()), this, SLOT(update()));
//    qDebug()<<"Tower created"<<"\n";
    // When Tower constructor is called gold saldo should decrease
    Game::game().gold->decreaseGold();
}

Tower::Tower(int x, int y, QString towerType)
    :Tower(Game::game().currentMap->getTilePointer(x,y),towerType)
{}


Tower::~Tower()
{

}
//check if current target is still in range
bool Tower::currentTargetInRange()
{
    if(target==nullptr)
        return false;
    if(target->collidesWithItem(attackArea))
        return true;
    else
        return false;
}
//target an enemy unit
void Tower::acquireTarget()
{
    QList<QGraphicsItem*> collidingItems=attackArea->collidingItems();
//    qDebug()<<collidingItems.count()<<"\n";
//    if(collidingItems.size()==1)
//    {
//        target=nullptr;
//        return;
//    }
    double closestDistance=MAXFLOAT;
    for (int i = 0; i < collidingItems.size(); i++) {
        EnemyUnit* enemyUnit=dynamic_cast<EnemyUnit*>(collidingItems[i]);
        if(enemyUnit!=nullptr)
        {
            double currentEnemyDistance=distanceTo(enemyUnit);
            if(currentEnemyDistance<closestDistance)
            {
                closestDistance=currentEnemyDistance;
                target=enemyUnit;
            }
        }
    }
//    if(target==nullptr)
//        qDebug()<<"No target"<<"\n";
//    else
//        qDebug()<<"Target acquired"<<target->getCurrentHealth()<<"\n";
}

void Tower::attack()
{
    if(target==nullptr || !target->isAlive)
        return;
//    target->takeDamage(getAttackDamage());
    turret->fire();
//    new Projectile(getAttackDamage(),30,QPointer<EnemyUnit>(getTarget()),this->pos()+QPointF(Game::game().tileWidth/2,Game::game().tileWidth/2));
    if(!target || !target->isAlive)
        target=nullptr;
//    qDebug()<<"Shots fired"<<"\n";
}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());
        return ln.length();
}
//getters


MapTile* Tower::getLocationOnMap() const
{
    return locationOnMap;
}
QGraphicsPolygonItem *Tower::getAttackArea() const
{
    return attackArea;
}

void Tower::acquireTargetAndAttack()
{
    if(target==nullptr || !currentTargetInRange())
    {
        target=nullptr;
        acquireTarget();
    }
    attack();
}

void Tower::update()
{
   numberOfTicks++;
   if(target==nullptr || !target->isAlive || !currentTargetInRange())
       target=nullptr;
   if(target!=nullptr)
       turret->rotateToTarget();
   if(numberOfTicks==attributes->getParameters()["attackSpeed"])
   {
       acquireTargetAndAttack();
       numberOfTicks=0;
   }
}

QRectF Tower::boundingRect() const
{
    int len=Game::game().tileWidth;
    return QRectF(0,0,attributes->getParameters()["tileWidth"]*len,attributes->getParameters()["tileHeight"]*len);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    QRectF towerRect(0,0,width*Game::game().tileWidth,height*Game::game().tileWidth);
//    painter->setBrush(Qt::);
//    painter->drawPolygon(getAttackArea()->polygon());
//    painter->setBrush(Qt::green);
//    painter->drawRect(QRectF(0,0,width*Game::game().tileWidth,height*Game::game().tileWidth));
    painter->drawPixmap(0,0,QPixmap(":/images/Tower32.png"));


}

