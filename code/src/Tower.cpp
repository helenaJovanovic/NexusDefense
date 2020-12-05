#include <code/include/Tower.hpp>
#include <cmath>



void Tower::setTarget(EnemyUnit *value)
{
    target = value;
}

Tower::Tower(MapTile* tile,float attackRange,int width,int height,QString spriteName)
    : locationOnMap(tile),width(width),height(height),spriteName(spriteName)
{
    this->setPos(this->locationOnMap->pos());
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
//    attackArea->setOpacity(0);
//    Game::game().scene->addItem(attackArea);
    Game::game().scene->addItem(this);
    connect(Game::game().gameTimer, SIGNAL(timeTickSignal()), this, SLOT(update()));
    qDebug()<<"Tower created"<<"\n";
}

Tower::Tower(int x, int y,float attackRange,int width,int height,QString spriteName)
    :Tower(Game::game().currentMap->getTilePointer(x,y),attackRange,width,height,spriteName)
{}
QString Tower::getSpriteName() const
{
    return spriteName;
}

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
    new Projectile(attackDamage,30,target,"projectile",this->pos()+QPointF(Game::game().tileWidth/2,Game::game().tileWidth/2));
    if(!target || !target->isAlive)
        target=nullptr;
    qDebug()<<"Shots fired"<<"\n";
}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());
        return ln.length();
}
//getters
float Tower::getAttackDamage() const
{
    return attackDamage;
}

float Tower::getAttackSpeed() const
{
    return attackSpeed;
}

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
   if(numberOfTicks==50)
   {
       acquireTargetAndAttack();
       numberOfTicks=0;
   }
}

int Tower::getWidth() const
{
    return width;
}

int Tower::getHeight() const
{
    return height;
}
QRectF Tower::boundingRect() const
{
    int len=Game::game().tileWidth;
    return QRectF(0,0,width*len,height*len);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    QRectF towerRect(0,0,width*Game::game().tileWidth,height*Game::game().tileWidth);
//    painter->setBrush(Qt::);
//    painter->drawPolygon(getAttackArea()->polygon());
    painter->setBrush(Qt::green);
    painter->drawRect(QRectF(0,0,width*Game::game().tileWidth,height*Game::game().tileWidth));


}

