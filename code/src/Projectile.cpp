#include <code/include/Projectile.hpp>
#define DelayFactor 16
#define UnitLength 29
#define UnitHeight 46
#define ProjectileLength 10
#define ProjectileHeight 20



Projectile::Projectile(float damage, float speed, QPointer<EnemyUnit> target, QString spriteName, QPointF startPosition)
    : damage(damage),speed(speed),target(target),spriteName(spriteName)
{
    this->setPos(startPosition);
    Game::game().scene->addItem(this);
    //initial direction
    this->setTransformOriginPoint(ProjectileLength/2,0);
    qreal x2=target->pos().rx()+UnitLength/2;
    qreal y2=target->pos().ry()+UnitHeight/2;
    qreal x1=this->pos().rx()+ProjectileLength/2;
    qreal y1=this->pos().ry()+ProjectileHeight/2;
    direction=QLineF(x1,y1,x2,y2);
    //initial angle
    this->setRotation(direction.angle());
    connect(Game::game().gameTimer, SIGNAL(timeTickSignal()), this, SLOT(update()));
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

QString Projectile::getSpriteName() const
{
    return spriteName;
}

QRectF Projectile::boundingRect() const
{
    return QRectF(0,0,ProjectileLength,ProjectileHeight);
}

void Projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::red);
    painter->drawRect(0,0,ProjectileLength,ProjectileHeight);
}

bool Projectile::impact()
{
    if(this->collidesWithItem(target))
    {
        target->takeDamage(damage);
        qDebug() << "Impact!" << "\n";
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
    moveBy(direction.dx()/DelayFactor,direction.dy()/DelayFactor);
}

void Projectile::rotateToTarget()
{
    qreal x2=target->pos().rx()+UnitLength/2;
    qreal y2=target->pos().ry()+UnitHeight/2;
    qreal x1=this->pos().rx()+ProjectileLength/2;
    qreal y1=this->pos().ry()+ProjectileHeight/2;
    QLineF newDirection=QLineF(x1,y1,x2,y2);
    qreal newRotation=rotation()-direction.angleTo(newDirection);
    this->setRotation(newRotation);
    direction=newDirection;
}

bool Projectile::targetAlive()
{
   if(target.isNull() || !target->isAlive)
   {
       qDebug()<<"target dead"<<"\n";
       return false;
   }
   qDebug()<<"target alive"<<"\n";
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


