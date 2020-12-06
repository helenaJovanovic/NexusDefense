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

        //When enemy unit is destroyed score and gold should increase
        Game::game().score->increase();
        Game::game().gold->increaseGold();

        delete(this);

        qDebug() << "Unit death" << "\n";
    }
}

void EnemyUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(0, 0, QPixmap(":/images/images/zombie.png"));
}

QRectF EnemyUnit::boundingRect() const {
    return QRectF(0, 0, 29, 46);
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

        // If the unit is not on the last direction we take the next turn
        if(nextTurnPointIndex < numOfTurns - 1){
            if(pos().rx() + 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 == turnPoints[nextTurnPointIndex].ry()){
                nextTurnPointIndex++;
                currentDirectionIndex++;

                currentDirection = turnDirections[currentDirectionIndex];
            }
        }

        // If it is the last direction we stop the unit in front of the nexus
        else{
            if((pos().rx() + 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 48 == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() - 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() + 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() - 16 == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() + 48 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 == turnPoints[nextTurnPointIndex].ry()))

                stopMovement = true;
            // nexus health should decrease
            Game::game().health->decrease();

        }

        numOfTicks = 0;
    }
}
