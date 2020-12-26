#include "code/include/Skeleton.hpp"

Skeleton::Skeleton(QPointF spawnPoint, int movementDelay)
    : EnemyUnit(movementDelay)
{
    unitSprite = Game::game().spriteLoader->getUnitSprite("Skeleton");
    unitSpriteMap = unitSprite->getStatesMap();

    currentSpritesheet = unitSprite->getSpritesheet();
    currentOriginPoint = unitSpriteMap["south"][frameNumber].origin;
    currentOriginRect = unitSpriteMap["south"][frameNumber].rect;

    offsetX = unitSprite->getOffsetX();
    offsetY = unitSprite->getOffsetY();

    healthBar.setRect(0, 0, currentOriginRect.width(), 5);
    healthBar.setParentItem(this);
    //healthBar.setVisible(false);

    explosionSprite = Game::game().spriteLoader->getUnitSprite("Batexp");
    explosionSpriteMap = explosionSprite->getStatesMap();

    setPos(spawnPoint.rx() + offsetX, spawnPoint.ry() + offsetY);

    Game::game().scene->addItem(this);

    isAlive = true;

    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::move);
    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::animate);
    connect(Game::game().gameTimer, &QTimer::timeout, this, &EnemyUnit::boom);
}
