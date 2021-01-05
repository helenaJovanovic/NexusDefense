
#include <code/include/Turret.hpp>
#define DelayFactor 16


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
    this->tower=tower;
    float barrelX=
            tower->getAttributes()->getParameters()["turretBarrelPercentageX"]/100
            *
            tower->getAttributes()->getParameters()["turretLength"];
    barrel=QPointF(tower->pos().x()+barrelX,tower->pos().y());
    float turretLength=tower->getAttributes()->getParameters()["turretLength"];
    float turretHeight=tower->getAttributes()->getParameters()["turretHeight"];
    float turretCenterX=
            tower->getAttributes()->getParameters()["turretCenterPercentageX"]/100
            *
            tower->getAttributes()->getParameters()["turretLength"];
    float turretCenterY=
            tower->getAttributes()->getParameters()["turretCenterPercentageY"]/100
            *
            tower->getAttributes()->getParameters()["turretHeight"];
//    qDebug()<<turretCenterX<<" - "<<turretCenterY<<"\n";
    this->setParent(tower);
//    this->setPos(tower->pos()+QPoint(Game::game().tileWidth/2-2*turretLength/3,-turretHeight/3));
    this->setPos(tower->pos()+QPoint(Game::game().tileWidth/2-turretCenterX,Game::game().tileWidth/2-turretCenterY));
    this->setTransformOriginPoint(turretCenterX,turretCenterY);
    direction=QLineF(this->pos()+QPointF(turretCenterX,turretCenterY),this->pos()+QPointF(turretCenterX,turretCenterY));

   fireSound = new QMediaPlayer();
   fireSound->setMedia(QUrl(tower->getAttributes()->getPaths()["fireSoundPath"]));
   fireSound->setVolume(30);

}

Turret::~Turret()
{

}

QRectF Turret::boundingRect() const
{
    return QRectF(0,0,tower->getAttributes()->getParameters()["turretLength"],tower->getAttributes()->getParameters()["turretHeight"]);
}

void Turret::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,QPixmap(tower->getAttributes()->getPaths()["turretImagePath"]));
}

void Turret::rotateToTarget()
{

//    qDebug()<<tower->getTarget()->getCurrentHealth();
//    qDebug()<<"It breaks here\n";
    //unit coordinates
    qreal x2=tower->getTarget()->pos().rx()+tower->getTarget()->boundingRect().center().x();
    qreal y2=tower->getTarget()->pos().ry()+tower->getTarget()->boundingRect().center().y();
    //turret tip coordinates
    qreal x3=this->pos().rx()+2*tower->getAttributes()->getParameters()["turretLength"]/3;
    qreal y3=this->pos().ry();
    //turret "center"coordinates
    qreal x1=this->pos().rx()+2*tower->getAttributes()->getParameters()["turretLength"]/3;
    qreal y1=this->pos().ry()+tower->getAttributes()->getParameters()["turretHeight"]/3;
    QLineF newDirection=QLineF(x1,y1,x2,y2);
    QLineF barrelVector(x1,y1,x3,y3);
    this->setRotation(-QLineF(x1,y1,x3,y3).angleTo(newDirection));
    barrelVector.setAngle(-QLineF(x1,y1,x3,y3).angleTo(newDirection));
    direction=newDirection;
    barrel=QPointF(barrelVector.x1(),barrelVector.y1());
}

void Turret::fire()
{

   if(fireSound->state() == QMediaPlayer::PlayingState) {
        fireSound->setPosition(0);
    }
   else if(fireSound->state() == QMediaPlayer::StoppedState) {
        fireSound->play();
    }
    new Projectile(tower->getAttributes()->getParameters()["blastRadius"],tower->getAttributes()->getParameters()["projectileLength"],tower->getAttributes()->getParameters()["projectileHeight"],tower->getAttributes()->getPaths()["projectileImagePath"],tower->getAttributes()->getParameters()["attackDamage"],tower->getAttributes()->getParameters()["projectileSpeedDelay"],tower->getTarget(),QPointF(barrel.x(),barrel.y()));
}
