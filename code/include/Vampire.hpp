#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP

#include "code/include/EnemyUnit.hpp"

class Vampire : public EnemyUnit{
public:
    Vampire(QPointF spawnPoint);

private slots:
   void spawnAdd();
};

#endif // VAMPIRE_HPP
