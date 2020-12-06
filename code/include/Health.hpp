#ifndef HEALTH_HPP
#define HEALTH_HPP

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
private:
    int health;
};


#endif // HEALTH_HPP
