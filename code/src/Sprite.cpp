#include <code/include/Sprite.hpp>


Sprite::Sprite(const QString& name) : name(name) {

}

Sprite::Sprite(const Sprite &) {
    //TODO: implement copy constructor
}

QString Sprite::getName() const {
    return name;
}
