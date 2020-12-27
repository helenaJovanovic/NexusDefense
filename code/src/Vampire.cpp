#include "code/include/Vampire.hpp"
#include "code/include/Bat.hpp"

Vampire::Vampire(QPointF spawnPoint)
    : EnemyUnit()
{
    unitSprite = Game::game().spriteLoader->getUnitSprite("Vampire");
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
    connect(Game::game().gameTimer, &QTimer::timeout, this, &Vampire::spawnAdd);
}

void Vampire::spawnAdd(){
    if(!isAlive)
        return;

    if(ticksElapsed % 400 == 0)
        new Bat(pos() - QPointF(offsetX, offsetY), currentDirectionIndex, nextTurnPointIndex, currentDirection);
}
