#include<code/include/Gold.hpp>
#include<QFont>

Gold::Gold(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    gold = 100;
    setPlainText(QString("Gold: ") + QString::number(gold));
    setDefaultTextColor(Qt::darkYellow);
    setFont(QFont("times",16));

}

void Gold::increaseGold() {
    gold+=100;
    setPlainText(QString("Gold: ") + QString::number(gold));
}

void Gold::decreaseGold() {
    gold-=100;
    setPlainText(QString("Gold: ") + QString::number(gold));
}

int Gold::getGold() {
    return gold;
}
