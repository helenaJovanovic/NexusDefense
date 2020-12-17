#include <code/include/Sprite.hpp>


Sprite::Sprite(const QString& name, const QString& spritesheet, const QString& initialState)
    : name(name), spritesheet(spritesheet), initialState(initialState) {

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

QMap<QString, QVector<Sprite::frame> > &Sprite::getStatesMap() {
    return animationStates;
}
