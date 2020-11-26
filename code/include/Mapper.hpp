#ifndef JSONMAPPER_HPP
#define JSONMAPPER_HPP

#include <QFile>
#include <QString>
#include <QVector>
#include <QPair>
#include <QPointF>

class Mapper
{
public:
    //Required: Path to map .txt file, resX, resY of screen
    Mapper(QString& path);

    //Returns true if file is opened succesfully
    bool readFile();

    //Size of one tile in pixels, with respect to current size of of area
    //where the map is being drawn (the resolution of the area where map
    //is drawn)
    QPair<int, int> getSizeOfTilePixels(int resX, int resY);

    //Amount of tiles in the grid in x and y coord
    QPair<int, int> getTilesNum();

    //Function that takes height, width of where the map is being drawn
    //and position of an object.
    //It returns the location in pixels of where the tile should be drawn.
    QPair<int, int> gridPosToPixels(int resX, int resY, QPair<int, int> gridPos);

    //Returns position in grid
    //---------------------------------------------------------------------
    QPair<int, int> getNexusXY();
    QPair<int, int> getUnitSpawnPointXY();
    QVector<QPair<int, int>>& getRoadTilesXY();
    QVector<QPair<int, int>>& getTowerTilesXY();
    QVector<QPair<int, int>>& getTurningRoadPoint();

    //Return unit path that returns QPointF vector
    //with points where a unit must turn
    //--->The pixels returned are positioned in the middle of the tile
    QVector<QPointF> getUnitTurnPointsXY(int resX, int resY);

    //Next we want the direction where to which
    //the unit must turn from that point

    //For each index in the unitTurnPoint vector
    //there is a corresponding direction in this vector
    QVector<unsigned>& getDirections();

    //Calculate direction using two points
    unsigned calcDirection(QPointF p1, QPointF p2);

private:

    int tilesX;
    int tilesY;
    int nexusX;
    int nexusY;
    int unitSpawnPointX;
    int unitSpawnPointY;

    QString path;

    QVector<QPointF> turningPointFs;
    /*
    1 for down
    2 for left
    3 for right
    4 for up
    */
    QVector<unsigned> directions;


    QVector<QPair<int, int>> roadToNexus;
    QVector<QPair<int, int>> turningPointRoad;
    QVector<QPair<int, int>> towerPositions;
};

#endif // JSONMAPPER_HPP
