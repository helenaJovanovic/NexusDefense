#ifndef GAMESCORE_HPP
#define GAMESCORE_HPP

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase();
    int getScore();
private:
    int score;
};

#endif // GAMESCORE_HPP
