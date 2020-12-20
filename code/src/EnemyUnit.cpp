#include <code/include/EnemyUnit.hpp>
#include <code/include/GameTimer.hpp>
#include <code/include/Mapper.hpp>

EnemyUnit::EnemyUnit(MapTile* spawnPoint, QString spriteName, int movementDelay)
    : isAlive(true), movementDelay(movementDelay)
{

    turnPoints = Game::game().currentMap->getTurnPoints();
    turnDirections = Game::game().currentMap->getTurnDirections();

    numOfTurns = turnPoints.length();

    nextTurnPointIndex = 0;
    currentDirectionIndex = 0;
    currentDirection = turnDirections[0];
    frameNumber = 0;
    deathFrameNumber = 0;
    timeElapsed = 0;

    unitSprite = Game::game().spriteLoader->getUnitSprite(spriteName);
    unitSpriteMap = unitSprite->getStatesMap();

    explosionSprite = Game::game().spriteLoader->getUnitSprite("Batexp");
    explosionSpriteMap = explosionSprite->getStatesMap();

    currentSpritesheet = unitSprite->getSpritesheet();

    healthBar.setRect(0, 0, 32, 5);
    healthBar.setParentItem(this);
    healthBar.setVisible(false);

    setPos(spawnPoint->pos());

    Game::game().scene->addItem(this);

    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::move);
    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::animate);
    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::boom);
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

        healthBar.setVisible(false);

        currentSpritesheet = explosionSprite->getSpritesheet();
        currentOriginPoint = explosionSpriteMap["boom"][0].origin;
        currentOriginRect = explosionSpriteMap["boom"][0].rect;

        timeElapsed = 0;

        deathPhase = true;
    }

    else
        healthBar.setRect(0, 0, static_cast<int>(32 * (currentHealth/maxHealth)), 5);
}

void EnemyUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(currentOriginPoint, currentSpritesheet, currentOriginRect);

    if(!deathPhase && currentHealth < maxHealth){
        painter->fillRect(healthBar.rect(), Qt::red);
        painter->drawRect(0, 0, 32, 5);
    }
}

QRectF EnemyUnit::boundingRect() const {
    return QRectF(0, 0, 32, 32);
}

void EnemyUnit::animate(){
    timeElapsed += 16;

    if(!isAlive)
        return;


    if(currentDirection == 1){

        if(frameNumber == unitSpriteMap["south"].size())
            frameNumber = 0;


        if(timeElapsed >= unitSpriteMap["south"][frameNumber].duration){

            currentOriginPoint = unitSpriteMap["south"][frameNumber].origin;
            currentOriginRect = unitSpriteMap["south"][frameNumber].rect;

             frameNumber++;

             timeElapsed = 0;
        }
    }

    else if(currentDirection == 3){

        if(frameNumber == unitSpriteMap["east"].size())
            frameNumber = 0;


        if(timeElapsed >= unitSpriteMap["east"][frameNumber].duration){

            currentOriginPoint = unitSpriteMap["east"][frameNumber].origin;
            currentOriginRect = unitSpriteMap["east"][frameNumber].rect;

            frameNumber++;

            timeElapsed = 0;
        }
    }


}

void EnemyUnit::move(){
    if(!isAlive){
        numOfTicks = 0;
        return;
    }

    numOfTicks++;

    if(numOfTicks >= movementDelay){

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

                timeElapsed = 0;
                frameNumber = 0;
            }
        }

        // If it is the last direction we stop the unit in front of the nexus
        else{
            if((pos().rx() + 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 48 == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() - 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() + 16 == turnPoints[nextTurnPointIndex].rx() && pos().ry() - 16 == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() + 48 == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 == turnPoints[nextTurnPointIndex].ry())){

                isAlive = false;

                this->takeDamage(currentHealth);
            }

        }

        numOfTicks = 0;
    }
}

void EnemyUnit::boom(){
    if(!deathPhase)
        return;

    timeElapsed += 16;

    if(deathFrameNumber == explosionSpriteMap["boom"].size()){

        Game::game().scene->removeItem(this);
        delete(this);
    }

    else if(timeElapsed >= explosionSpriteMap["boom"][deathFrameNumber].duration){
        currentOriginPoint = explosionSpriteMap["boom"][deathFrameNumber].origin;
        currentOriginRect = explosionSpriteMap["boom"][deathFrameNumber].rect;

        this->update();

        deathFrameNumber++;

        timeElapsed = 0;
    }


}
