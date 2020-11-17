#ifndef MAP_HPP
#define MAP_HPP

#include "MapTile.hpp"
#include "Mapper.hpp"

#include <QObject>

// All map related information goes here

// Currently it inherits QObject (not sure if needed atm)

class Map : public QObject {
    Q_OBJECT
public:
    Map(Mapper*);
    //virtual ~Map() {}

    // The map of the map... Key is "x, y" where x and y are positions of the tile in tiles (not pixels)
    // P.S. the map tile coordinates start from 1, 1 !!
    QMap<QString, MapTile*> map;

    // Pointers to nexus and spawn for quick access (i.e unit spawn)
    MapTile *nexusPointer;
    MapTile *unitSpawnPointer;

    // TODO: Initialize during constructor (create a QPoint for every road tile)
    // Keeps the positions of road tiles (for enemyUnits movement)
    QVector<QPoint> enemyRoad;


    // Returns a pointer to the MapTile located at (x, y) map tile coordinates, or nullptr if not found
    MapTile *getTilePointer(int x, int y);
};

#endif // MAP_HPP
