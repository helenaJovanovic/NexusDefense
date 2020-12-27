#ifndef BAT_HPP
#define BAT_HPP

#include "code/include/EnemyUnit.hpp"

class Bat : public EnemyUnit{
public:
    Bat(QPointF spawnPoint);

    Bat(QPointF spawnPoint, const unsigned newDirectionIndex, const unsigned newTurnPointIndex, const DirectionsEnum newDirection);
};
#endif // BAT_HPP
