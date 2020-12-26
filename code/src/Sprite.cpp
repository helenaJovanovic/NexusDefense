#include <code/include/Sprite.hpp>


Sprite::Sprite(const QString& name, const QString& spritesheet, const QString& initialState, const int offsetX, const int offsetY)
    : name(name), spritesheet(spritesheet), initialState(initialState), offsetX(offsetX), offsetY(offsetY) {

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

QMap<QString, QVector<Sprite::frame> > &Sprite::getStatesMap() {
    return animationStates;
}
