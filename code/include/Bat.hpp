#ifndef BAT_HPP
#define BAT_HPP

#include "code/include/EnemyUnit.hpp"

class Bat : public EnemyUnit{
public:
    Bat(QPointF spawnPoint, const int movementDelay);

    Bat(QPointF spawnPoint, const int movementDelay,
        const unsigned newDirectionIndex, const unsigned newTurnPointIndex, const int newDirection);
};
#endif // BAT_HPP
