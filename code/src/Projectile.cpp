#include <code/include/Projectile.hpp>
#include <cmath>
#define DelayFactor 16
#define UnitLength 32
#define UnitHeight 32
#define ProjectileLength 10
#define ProjectileHeight 25



Projectile::Projectile(float blastRadius,float length, float height, QString imagePath, float damage, float speed, QPointer<EnemyUnit> target, QPointF startPosition)
    : blastRadius(blastRadius),damage(damage),speed(speed),target(target),length(length),height(height),imagePath(imagePath)
{
    this->setPos(startPosition);
    Game::game().scene->addItem(this);
    //initial direction
    this->setTransformOriginPoint(length/2.0,height/2.0);
    qreal x2=target->pos().rx()+UnitLength/2;
    qreal y2=target->pos().ry()+UnitHeight/2;
    qreal x1=this->pos().rx()+length/2;
    qreal y1=this->pos().ry()+height/2;
    direction=QLineF(x1,y1,x2,y2);
    //initial angle
    this->setRotation(direction.angle());
    connect(Game::game().gameTimer, SIGNAL(timeout()), this, SLOT(update()));
}


Projectile::~Projectile()
{

}
float Projectile::getDamage() const
{
    return damage;
}

float Projectile::getSpeed() const
{
    return speed;
}

QPointer<EnemyUnit> Projectile::getTarget() const
{
    return target;
}

QRectF Projectile::boundingRect() const
{
    return QRectF(0,0,length,height);
}

void Projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    painter->setBrush(Qt::red);
//    painter->drawRect(0,0,ProjectileLength,ProjectileHeight);
    painter->drawPixmap(0,0,imagePath);
}

bool Projectile::impact()
{
    if(this->collidesWithItem(target))
    {
        if(!blastRadius)
            target->takeDamage(damage);
        else
        {

//             QVector<QPointF> rangeOctagonPoints;
//             float angleDegrees=0;
//             for (int i = 0; i < 8; i++) {
//                 float angleRads=angleDegrees*M_PI/180.0;
//                 rangeOctagonPoints << QPoint(pos().x()+blastRadius*cos(angleRads),pos().y()+blastRadius*sin(angleRads));
//                 angleDegrees+=45;
//             }
//             QGraphicsPolygonItem* blastArea=new QGraphicsPolygonItem(QPolygonF(rangeOctagonPoints),this);
            QGraphicsEllipseItem* blastArea=new QGraphicsEllipseItem(target->pos().x(),target->pos().y(),blastRadius,blastRadius);
//            blastArea->setPos(this->pos());
//            blastArea->setBrush(QBrush(Qt::red));
            qDebug()<< blastArea->pos() << "\n";
            Game::game().scene->addItem(blastArea);
            QList<QGraphicsItem*> enemiesInRadius=blastArea->collidingItems();
            qDebug() << "------------------" << "\n";
            for (int i = 0; i < enemiesInRadius.size(); i++) {
                EnemyUnit* enemyUnit=dynamic_cast<EnemyUnit*>(enemiesInRadius[i]);
                if(enemyUnit!=nullptr)
                {
                    qDebug() << "enemy" << "\n";
                    enemyUnit->takeDamage(damage);
                }
            }
            qDebug() << "------------------" << "\n";
            Game::game().scene->removeItem(blastArea);
            delete blastArea;
        }
//        qDebug() << "Impact!" << "\n";
        Game::game().scene->removeItem(this);
        delete(this);
        return true;
    }
    return false;
}

void Projectile::moveToTarget()
{
    //TODO getting dynamic unit size
//    if(targetAlive())
//    {
//        qreal x2=target->pos().rx()+UnitLength/2;
//        qreal y2=target->pos().ry()+UnitHeight/2;
//        qreal x1=this->pos().rx();
//        qreal y1=this->pos().ry();


//        moveBy((x2-x1)/DelayFactor,(y2-y1)/DelayFactor);
//    }
    moveBy(direction.dx()/speed,direction.dy()/speed);
}

void Projectile::rotateToTarget()
{
    qreal x2=target->pos().rx()+UnitLength/2;
    qreal y2=target->pos().ry()+UnitHeight/2;
    qreal x1=this->pos().rx()+length/2;
    qreal y1=this->pos().ry()+length/2;
    qreal x3=this->pos().rx()+length/2;
    qreal y3=this->pos().ry();
    QLineF newDirection=QLineF(x1,y1,x2,y2);
//    qreal newRotation=rotation()-direction.angleTo(newDirection);
    qreal newRotation=-QLineF(x1,y1,x3,y3).angleTo(newDirection);
    this->setRotation(newRotation);
    direction=newDirection;
}

bool Projectile::targetAlive()
{
   if(target.isNull() || !target->isAlive)
   {
//       qDebug()<<"target dead"<<"\n";
       return false;
   }
//   qDebug()<<"target alive"<<"\n";
   return true;

}


void Projectile::update()
{
    if(targetAlive())
    {
        rotateToTarget();
        moveToTarget();
        impact();
    }
    else
    {
        Game::game().scene->removeItem(this);
        delete(this);
    }
}


