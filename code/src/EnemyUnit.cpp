#include <code/include/EnemyUnit.hpp>

EnemyUnit::EnemyUnit(QPointF spawnPoint)
    : isAlive(true)
{
    this->pos() = spawnPoint;

    Game::game().scene->addItem(this);

    qDebug() << "Unit created" << "\n";
}

EnemyUnit::~EnemyUnit(){

}

//Getters
float EnemyUnit::getMaxHealth() const{
    return this->maxHealth;
}

float EnemyUnit::getCurrentHealth() const{
    return this->currentHealth;
}

float EnemyUnit::getMovementSpeed() const{
    return this->movementSpeed;
}

//Methods for unit functionality
void EnemyUnit::takeDamage(float damageAmount) {
    this->currentHealth -= damageAmount;

    if(this->currentHealth <= 0){
        this->isAlive = false;

        //TODO: Death animation

        Game::game().scene->removeItem(this);

        delete(this);

        qDebug() << "Unit death" << "\n";
    }
}

void EnemyUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    int len = Game::game().tileWidth;
    QRectF unitRect(0, 0, len, len);

    painter->setBrush(Qt::red);
    painter->drawRect(unitRect);

    QString typeString = QString("EN");

    painter->drawText(8, 15, typeString);
}

QRectF EnemyUnit::boundingRect() const {
    int len = Game::game().tileWidth;
    return QRectF(0, 0, len, len);
}

