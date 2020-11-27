#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <QMap>
#include <QRect>
#include <QString>


//Container class for all relevant spritesheet information.
class Sprite {
public:
    Sprite(const QString&);
    Sprite(const Sprite&);

    QString getName() const;
private:
    QString name;
    QMap<QString, QVector<QRect>> animationStates;
};

#endif // SPRITE_HPP
