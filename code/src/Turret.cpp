
#include <code/include/Turret.hpp>
#define DelayFactor 16
#define UnitLength 29
#define UnitHeight 46
#define TurretLength 16
#define TurretHeight 33

QLineF Turret::getDirection() const
{
    return direction;
}

void Turret::setDirection(const QLineF &value)
{
    direction = value;
}

Turret::Turret(Tower *tower)
{
    this->setParent(tower);
    this->setPos(tower->pos()+QPoint(Game::game().tileWidth/2-TurretLength/2,-TurretHeight/2));
    this->setTransformOriginPoint(TurretLength/2.0,TurretHeight/2.0);
    direction=QLineF(this->pos()+QPointF(TurretLength/2,TurretHeight/2),this->pos()+QPointF(TurretLength/2,TurretHeight/2));
    fireSound = new QMediaPlayer();
    fireSound->setMedia(QUrl("qrc:/sounds/projectile.mp3"));
    fireSound->setVolume(80);

}

Turret::~Turret()
{

}

QRectF Turret::boundingRect() const
{
    return QRectF(0,0,TurretLength,TurretHeight);
}

void Turret::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,QPixmap(":/images/images/MG16x33.png"));
}

void Turret::rotateToTarget()
{
    qreal x2=tower->getTarget()->pos().rx()+UnitLength/2;
    qreal y2=tower->getTarget()->pos().ry()+UnitHeight/2;
    qreal x1=this->pos().rx()+TurretLength/2;
    qreal y1=this->pos().ry()+TurretHeight/2;
    QLineF newDirection=QLineF(x1,y1,x2,y2);
    qreal newRotation=rotation()-direction.angleTo(newDirection);
    this->setRotation(newRotation);
    direction=newDirection;
}

void Turret::fire()
{
    new Projectile(tower->getAttackDamage(),30,QPointer<EnemyUnit>(tower->getTarget()),this->pos()+QPointF(Game::game().tileWidth/2,Game::game().tileWidth/2));
    if(fireSound->state()==QMediaPlayer::PlayingState)
        fireSound->setPosition(0);
    else if(fireSound->state()== QMediaPlayer::StoppedState)
        fireSound->play();

}
