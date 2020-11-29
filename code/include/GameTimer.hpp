#ifndef GAMETIMER_HPP
#define GAMETIMER_HPP

#include <QObject>
#include <QTimer>
#include <QDebug>

class GameTimer : public QObject {
    Q_OBJECT

public:
    GameTimer();
    QTimer *timer;

public slots:
    void timeTickSlot();

signals:
    void timeTickSignal();
};

#endif // GAMETIMER_HPP
