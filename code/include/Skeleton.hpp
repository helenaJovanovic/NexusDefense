#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "code/include/EnemyUnit.hpp"

class Skeleton : public EnemyUnit{

public:
    Skeleton(QPointF spawnPoint, int movementDelay);
};

#endif // SKELETON_HPP
