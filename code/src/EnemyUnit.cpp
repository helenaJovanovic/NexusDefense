#include <code/include/EnemyUnit.hpp>
#include <code/include/Game.hpp>
#include <code/include/MapTile.hpp>

#include <QPainter>

EnemyUnit::EnemyUnit(){

    Game::game().scene->addItem(this);

    this->isAlive = true;

}

void EnemyUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    int len = Game::game().tileWidth;
    QRectF unitRect(0, 0, len, len);

    painter->setBrush(Qt::red);
    painter->drawRect(unitRect);

    QString typeString = QString("EN");

    painter->drawText(8, 15, typeString);
}

QRectF EnemyUnit::boundingRect() const {
    int len = Game::game().tileWidth;
    return QRectF(0, 0, len, len);
}

