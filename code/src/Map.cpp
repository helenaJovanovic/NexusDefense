#include <code/include/Map.hpp>
#include <code/include/Game.hpp>
#include <QDebug>


// When the map is created, it utilizes a parser object (Mapper),
// from which it takes relevant information about the map, and fills the
// map container

Map::Map(Mapper* parser) {
    if(parser->readFile() == true) {




        // The area of the scene in which the map gets put, in pixels
        int resX = Game::game().tileWidth * parser->getTilesNum().first;
        int resY = Game::game().tileWidth * parser->getTilesNum().second;

        turnPoints = parser->getUnitTurnPointsXY(resX, resY);
        turnDirections = parser->getDirections();

        QPair<int, int> unitSpawnTile = parser->getUnitSpawnPointXY();
        QPair<int, int> nexusTile = parser->getNexusXY();

        // Go through all the road tiles and add them to the map with proper tags
        for(auto p: parser->getRoadTilesXY()) {
            QString key = QString(QString(p.first) + ", " + QString(p.second));
            QPair<int, int> position = parser->gridPosToPixels(resX, resY, {p.first, p.second});

            map[key] = new MapTile("E");
            map[key]->setPos(position.first, position.second);
            if(unitSpawnTile == p) {
                map[key]->isUnitSpawn = true;
                unitSpawnPointer = map[key];
            }

            if(nexusTile == p) {
                map[key]->isNexus = true;
                nexusPointer = map[key];
            }


            Game::game().scene->addItem(map[key]);
        }

        // Analog to road tiles, but with towers.
        // By default, you shouldn't be able to build towers on the nexus tile.
        for(auto p: parser->getTowerTilesXY()) {
            QString key = QString(QString(p.first) + ", " + QString(p.second));
            QPair<int, int> position = parser->gridPosToPixels(resX, resY, {p.first, p.second});

            if(map.contains(key)) {
                map[key]->type = QString("TE");
            } else {
                map[key] = new MapTile("T");
                map[key]->setPos(position.first, position.second);

                if(nexusTile == p) {
                    qDebug() << "Error: You shouldn't be able to build on Nexus.";
                }

                Game::game().scene->addItem(map[key]);
            }
        }

        delete parser;
    } else {
        delete parser;
        qDebug() << "Error parsing the map file.";

        exit(1); // TODO: Add error handling rather than simple exit.
    }
}

MapTile *Map::getTilePointer(int x, int y) {
    QString key = QString(x) + ", " + QString(y);
    if(!map.contains(key)) {
        return nullptr;
    } else {
        return map[key];
    }
}

QVector<QPointF>& Map::getTurnPoints(){
    return turnPoints;
}
QVector<unsigned>& Map::getTurnDirections(){
    return turnDirections;
}
