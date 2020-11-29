#include <code/include/GameTimer.hpp>

GameTimer::GameTimer()
    : timer(new QTimer(this))
{
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timeTickSlot()));
    timer->start(16);
}

void GameTimer::timeTickSlot(){
    emit timeTickSignal();
}
