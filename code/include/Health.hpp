#ifndef HEALTH_HPP
#define HEALTH_HPP

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem {
   Q_OBJECT
public:
    Health(QGraphicsItem * parent=0);
    void decrease(int dmgAmount);
    int getHealth();
signals:
    void dead();
private:
    int health;
};


#endif // HEALTH_HPP
