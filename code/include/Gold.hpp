#ifndef GOLD_HPP
#define GOLD_HPP

#include <QGraphicsTextItem>

class Gold: public QGraphicsTextItem{
public:
    Gold(QGraphicsItem * parent=0);
    void increaseGold();
    void decreaseGold();
    int getGold();
private:
    int gold;
};

#endif // GOLD_HPP
