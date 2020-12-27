#include <code/include/Health.hpp>
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    health = 10000;

    // Draw the text
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
}

void Health::decrease(int damageAmount){
    health-=damageAmount;
    setPlainText(QString("Health: ") + QString::number(health));
    if(health == 0)
        emit dead();
}

int Health::getHealth(){
    return health;
}
