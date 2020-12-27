#include <code/include/EnemyUnit.hpp>
#include <code/include/GameTimer.hpp>
#include <code/include/Mapper.hpp>

EnemyUnit::EnemyUnit(const int movementDelay)
    : movementDelay(movementDelay)
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
}

EnemyUnit::EnemyUnit(const int movementDelay,
            const unsigned newDirectionIndex, const unsigned newTurnPointIndex, const int newDirection)
    : EnemyUnit(movementDelay)
{

    currentDirectionIndex = newDirectionIndex;
    nextTurnPointIndex = newTurnPointIndex;
    currentDirection = newDirection;

    dyingSound = new QMediaPlayer();
    dyingSound->setMedia(QUrl("qrc:/sounds/scream.mp3"));
    dyingSound->setVolume(100);

    Game::game().scene->addItem(this);

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

        /*
        if(dyingSound->state()==QMediaPlayer::PlayingState)
            dyingSound->setPosition(0);
        else if(dyingSound->state()== QMediaPlayer::StoppedState)
            dyingSound->play();*/

        healthBar.setVisible(false);

        currentSpritesheet = explosionSprite->getSpritesheet();
        currentOriginPoint = explosionSpriteMap["boom"][0].origin;
        currentOriginRect = explosionSpriteMap["boom"][0].rect;
		
		//When enemy unit is destroyed score and gold should increase
        Game::game().score->increase();
        Game::game().gold->increaseGold();		

        timeElapsed = 0;

        deathPhase = true;
    }

    else
        healthBar.setRect(0, 0, static_cast<int>(currentOriginRect.width() * (currentHealth/maxHealth)), 5);
}

void EnemyUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(currentOriginPoint, currentSpritesheet, currentOriginRect);

    if(!deathPhase /*&& currentHealth < maxHealth*/){
        painter->fillRect(healthBar.rect(), Qt::red);
        painter->drawRect(0, 0, currentOriginRect.width(), 5);
    }
}

QRectF EnemyUnit::boundingRect() const {
    return currentOriginRect;
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
    ticksElapsed++;

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
            if(pos().rx() + 16 - offsetX == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 - offsetY == turnPoints[nextTurnPointIndex].ry()){

                nextTurnPointIndex++;
                currentDirectionIndex++;

                currentDirection = turnDirections[currentDirectionIndex];

                timeElapsed = 0;
                frameNumber = 0;

                this->takeDamage(30);

                update();
            }
        }

        // If it is the last direction we stop the unit in front of the nexus
        else{
            if((pos().rx() + 16 - offsetX == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 48 - offsetY == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() - 16 - offsetX == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 - offsetY == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() + 16 - offsetX == turnPoints[nextTurnPointIndex].rx() && pos().ry() - 16 - offsetY == turnPoints[nextTurnPointIndex].ry())
                || (pos().rx() + 48 - offsetX == turnPoints[nextTurnPointIndex].rx() && pos().ry() + 16 - offsetY == turnPoints[nextTurnPointIndex].ry())){

                isAlive = false;
				// nexus health should decrease
	            Game::game().health->decrease();
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
		
		// nexus health should decrease
        Game::game().health->decrease();

        update();

        deathFrameNumber++;

        timeElapsed = 0;
    }


}
