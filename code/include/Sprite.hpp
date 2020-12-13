#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <QMap>
#include <QRect>
#include <QString>
#include <QVector>

//Container class for all relevant spritesheet information.
class Sprite {

public:
    struct frame {
        int duration;
        QPoint origin;
        QRect rect;
    };

    Sprite(const QString&, const QString&, const QString&);

    QString getName() const;
    QString getSpritesheet() const;
    QString getInitialState() const;
    QMap<QString, QVector<frame>>& getStatesMap();

private:
    QString name;
    QString spritesheet;
    QString initialState;

    QMap<QString, QVector<frame>> animationStates;

    friend class SpriteLoader;
};



#endif // SPRITE_HPP
