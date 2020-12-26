#include "code/include/Bat.hpp"

Bat::Bat(QPointF spawnPoint, const int movementDelay)
    : EnemyUnit(movementDelay)
{
    unitSprite = Game::game().spriteLoader->getUnitSprite("Bat");
    unitSpriteMap = unitSprite->getStatesMap();

    currentSpritesheet = unitSprite->getSpritesheet();
    currentOriginPoint = unitSpriteMap["south"][frameNumber].origin;
    currentOriginRect = unitSpriteMap["south"][frameNumber].rect;

    offsetX = unitSprite->getOffsetX();
    offsetY = unitSprite->getOffsetY();

    setPos(spawnPoint.rx() + offsetX, spawnPoint.ry() + offsetY);

    healthBar.setRect(0, 0, currentOriginRect.width(), 5);
    healthBar.setParentItem(this);
    //healthBar.setVisible(false);

    explosionSprite = Game::game().spriteLoader->getUnitSprite("Batexp");
    explosionSpriteMap = explosionSprite->getStatesMap();

    Game::game().scene->addItem(this);

    isAlive = true;

    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::move);
    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::animate);
    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::boom);
}

Bat::Bat(QPointF spawnPoint, const int movementDelay,
         const unsigned newDirectionIndex, const unsigned newTurnPointIndex, const int newDirection)
    : Bat(spawnPoint, movementDelay)

{
    currentDirectionIndex = newDirectionIndex;
    nextTurnPointIndex = newTurnPointIndex;
    currentDirection = newDirection;
}
