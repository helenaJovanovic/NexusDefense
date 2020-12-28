#include "code/include/Bat.hpp"

Bat::Bat(QPointF spawnPoint)
    : EnemyUnit()
{
    unitSprite = Game::game().spriteLoader->getUnitSprite("Bat");
    unitSpriteMap = unitSprite->getStatesMap();

    currentSpritesheet = unitSprite->getSpritesheet();
    currentOriginPoint = unitSpriteMap["south"][frameNumber].origin;
    currentOriginRect = unitSpriteMap["south"][frameNumber].rect;

    offsetX = unitSprite->getOffsetX();
    offsetY = unitSprite->getOffsetY();
    movementDelay = unitSprite->getMovementDelay();
    attackDamage = unitSprite->getAttackDamage();
    maxHealth = unitSprite->getMaxHealth();
    currentHealth = maxHealth;

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

Bat::Bat(QPointF spawnPoint, const unsigned newDirectionIndex, const unsigned newTurnPointIndex, const DirectionsEnum newDirection)
    : Bat(spawnPoint)

{
    currentDirectionIndex = newDirectionIndex;
    nextTurnPointIndex = newTurnPointIndex;
    currentDirection = newDirection;
}
