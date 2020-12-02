#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <QMap>
#include <QRect>
#include <QString>
#include <QVector>

//Container class for all relevant spritesheet information.
class Sprite {
private:
    QString name;
    QString spritesheet;
    QString initialState;

    struct frame {
        int duration;
        QPoint origin;
        QRect rect;
    };

    QMap<QString, QVector<frame>> animationStates;

    friend class SpriteLoader;
public:
    Sprite(const QString&, const QString&, const QString&);

    QString getName() const;
    QMap<QString, QVector<frame>>& getStatesMap();
};



#endif // SPRITE_HPP
