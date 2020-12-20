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
    timeElapsed = 0;

    sprite = Game::game().spriteLoader->getUnitSprite(spriteName);
    spriteMap = sprite->getStatesMap();

    setPos(spawnPoint->pos());

    dyingSound = new QMediaPlayer();
    dyingSound->setMedia(QUrl("qrc:/sounds/scream.mp3"));
    dyingSound->setVolume(100);

    Game::game().scene->addItem(this);

    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::move);
    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::animate);
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

        if(dyingSound->state()==QMediaPlayer::PlayingState)
            dyingSound->setPosition(0);
        else if(dyingSound->state()== QMediaPlayer::StoppedState)
            dyingSound->play();

        Game::game().scene->removeItem(this);

        //When enemy unit is destroyed score and gold should increase
        Game::game().score->increase();
        Game::game().gold->increaseGold();

        delete(this);
    }
}

void EnemyUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(currentOriginPoint, sprite->getSpritesheet(), currentOriginRect);
}

QRectF EnemyUnit::boundingRect() const {
    return QRectF(0, 0, 32, 32);
}

void EnemyUnit::animate(){
    timeElapsed += 16;

    if(currentDirection == 1){

        if(frameNumber == spriteMap["south"].size()){
            frameNumber = 0;
        }

        if(timeElapsed >= spriteMap["south"][frameNumber].duration){

            currentOriginPoint = spriteMap["south"][frameNumber].origin;
            currentOriginRect = spriteMap["south"][frameNumber].rect;

            frameNumber++;

            timeElapsed = 0;
        }
    }

    else if(currentDirection == 3){

        if(frameNumber == spriteMap["east"].size()){
            frameNumber = 0;
        }

        if(timeElapsed >= spriteMap["east"][frameNumber].duration){

            currentOriginPoint = spriteMap["east"][frameNumber].origin;
            currentOriginRect = spriteMap["east"][frameNumber].rect;

            frameNumber++;

            timeElapsed = 0;
        }
    }
}

void EnemyUnit::move(){
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

                timeElapsed = 0;
                frameNumber = 0;
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

            takeDamage(maxHealth);

        }

        numOfTicks = 0;
    }
}
