#include <code/include/Sprite.hpp>


Sprite::Sprite(const QString& name, const QString& spritesheet, const QString& initialState,
               const int offsetX, const int offsetY, const int movementDelay, const int attackDamage, const int maxHealth)
    : name(name), spritesheet(spritesheet), initialState(initialState),
      offsetX(offsetX), offsetY(offsetY), movementDelay(movementDelay), attackDamage(attackDamage), maxHealth(maxHealth) {

}

QString Sprite::getName() const {
    return name;
}

QString Sprite::getSpritesheet() const {
    return spritesheet;
}

QString Sprite::getInitialState() const {
    return initialState;
}

int Sprite::getOffsetX() const {
    return offsetX;
}

int Sprite::getOffsetY() const {
    return offsetY;
}

int Sprite::getMovementDelay() const
{
    return movementDelay;
}

int Sprite::getAttackDamage() const
{
    return attackDamage;
}

void Sprite::increaseAttackDamage(const int damagePercent)
{
    attackDamage += static_cast<int>(attackDamage * (damagePercent/100.0));
}

int Sprite::getMaxHealth() const
{
    return maxHealth;
}

void Sprite::increaseMaxHealth(const int healthPercent)
{
    maxHealth += static_cast<int>(maxHealth * (healthPercent/100.0));
}

QMap<QString, QVector<Sprite::frame> > &Sprite::getStatesMap() {
    return animationStates;
}
