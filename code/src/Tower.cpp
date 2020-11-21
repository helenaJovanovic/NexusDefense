#include <code/include/Tower.hpp>
#include <cmath>



Tower::Tower(MapTile* tile,float attackRange,int width,int height)
    : locationOnMap(tile),width(width),height(height)
{
    this->pos()=this->locationOnMap->pos();
    Game::game().scene->addItem(this);
    QVector<QPointF> rangeOctagonPoints;
    QPointF towerCenter((width*Game::game().tileWidth)/2,(height*Game::game().tileWidth)/2);
    //octagon points,one on each 45 degrees
    float angleDegrees=0;
    for (int i = 0; i < 7; i++) {
        float angleRads=angleDegrees*M_PI/180.0;
        rangeOctagonPoints << QPoint(towerCenter.x()+attackRange*cos(angleRads),towerCenter.y()+attackRange*sin(angleRads));
        angleDegrees+=45;
    }
    attackArea=new QGraphicsPolygonItem(QPolygonF(rangeOctagonPoints),this);
    attackArea->setPos(towerCenter.x(),towerCenter.y());
    Game::game().scene->addItem(attackArea);
    qDebug()<<"Tower created"<<"\n";
}

Tower::Tower(int x, int y,float attackRange,int width,int height)
: width(width),height(height)
{
    locationOnMap=Game::game().currentMap->getTilePointer(x,y);
    this->pos()=this->locationOnMap->pos();
    Game::game().scene->addItem(this);
    QVector<QPointF> rangeOctagonPoints;
    QPointF towerCenter((width*Game::game().tileWidth)/2,(height*Game::game().tileWidth)/2);
    //octagon points
    float angleDegrees=0;
    for (int i = 0; i < 8; i++) {
        float angleRads=angleDegrees*M_PI/180.0;
        rangeOctagonPoints << QPoint(towerCenter.x()+attackRange*cos(angleRads),towerCenter.y()+attackRange*sin(angleRads));
        angleDegrees+=45;
    }
    attackArea=new QGraphicsPolygonItem(QPolygonF(rangeOctagonPoints),this);
    attackArea->setPos(towerCenter.x(),towerCenter.y());
    Game::game().scene->addItem(attackArea);
    qDebug()<<"Tower created"<<"\n";
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
    if(collidingItems.size()==1)
    {
        target=nullptr;
        return;
    }
    double closestDistance=MAXFLOAT;
    for (int i = 0; i < collidingItems.size(); i++) {
        EnemyUnit* enemyUnit=dynamic_cast<EnemyUnit*>(collidingItems[i]);
        if(enemyUnit)
        {
            double currentEnemyDistance=distanceTo(enemyUnit);
            if(currentEnemyDistance<closestDistance)
            {
                closestDistance=currentEnemyDistance;
                target=enemyUnit;
            }
        }
    }
}

void Tower::attack()
{
    if(target==nullptr)
        return;
    target->takeDamage(getAttackDamage());
    if(!target || !target->isAlive)
        target=nullptr;
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
        acquireTarget();
    attack();
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

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF towerRect(0,0,width*Game::game().tileWidth,height*Game::game().tileWidth);
    painter->setBrush(Qt::green);
    painter->drawRect(towerRect);

    painter->setBrush(Qt::gray);
    painter->drawPolygon(getAttackArea()->polygon());
}

