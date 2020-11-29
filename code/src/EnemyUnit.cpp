#include <code/include/EnemyUnit.hpp>
#include <code/include/GameTimer.hpp>
#include <code/include/Mapper.hpp>

EnemyUnit::EnemyUnit(QPointF spawnPoint)
    : isAlive(true)
{
    turnPoints = Game::game().currentMap->getTurnPoints();
    turnDirections = Game::game().currentMap->getTurnDirections();

    numOfTurns = turnPoints.length();

    nextTurnPointIndex = 0;

    currentDirectionIndex = 0;
    currentDirection = turnDirections[0];

    setPos(spawnPoint.rx(), spawnPoint.ry());

    Game::game().scene->addItem(this);

    connect(Game::game().gameTimer, SIGNAL(timeTickSignal()), this, SLOT(update()));

    qDebug() << "Unit created" << "\n";
}

EnemyUnit::~EnemyUnit(){

}

//Getters
float EnemyUnit::getMaxHealth() const{
    return maxHealth;
}

float EnemyUnit::getCurrentHealth() const{
    return currentHealth;
}

float EnemyUnit::getMovementDelay() const{
    return movementDelay;
}

//Setters
void EnemyUnit::setMovementDelay(int movementDelay){
    this->movementDelay = movementDelay;
}

//Methods for unit functionality
void EnemyUnit::takeDamage(float damageAmount) {
    currentHealth -= damageAmount;

    if(currentHealth <= 0){
        isAlive = false;

        //TODO: Death animation

        Game::game().scene->removeItem(this);

        delete(this);

        qDebug() << "Unit death" << "\n";
    }
}

void EnemyUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(0, 0, QPixmap(":/images/images/zombie.png"));
}

QRectF EnemyUnit::boundingRect() const {
    return QRectF(0, 0, 30, 47);
}

void EnemyUnit::update(){
    if(stopMovement){
        numOfTicks = 0;
        return;
    }

    this->numOfTicks++;

    if(numOfTicks == movementDelay){
        /*
        1 for down
        2 for left
        3 for right
        4 for up
        */

        if(currentDirection == 1)
            moveBy(0, 4);
        else if(currentDirection == 2)
            moveBy(-4, 0);
        else if(currentDirection == 3)
            moveBy(4, 0);
        else if(currentDirection == 4)
            moveBy(0, -4);

        if(nextTurnPointIndex < numOfTurns - 1){
            if(pos().rx() + 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 == turnPoints[nextTurnPointIndex].ry()){
                nextTurnPointIndex++;
                currentDirectionIndex++;

                currentDirection = turnDirections[currentDirectionIndex];
            }
        }

        else if(pos().rx() + 48 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 == turnPoints[nextTurnPointIndex].ry())
            stopMovement = true;

        numOfTicks = 0;
    }

    //qDebug() << "*****" << "\n";
}



