#ifndef JSONMAPPER_HPP
#define JSONMAPPER_HPP

#include <QFile>
#include <QString>


class Mapper
{
public:
    //Required: Path to map .txt file, resX, resY of screen
    Mapper(QString& path);

    //Returns true if file is opened succesfully
    bool readFile();
    //Enables easy reading of lines in format of
    // poslist : [x1, y1], [x2, y2]
    //with ", " being a seperator
    void loadArrayString(QString& line, QVector<QPair<int, int>> &obj);

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

private:

    int tilesX;
    int tilesY;
    int nexusX;
    int nexusY;
    int unitSpawnPointX;
    int unitSpawnPointY;

    QString path;

    QVector<QPair<int, int>> roadToNexus;
    QVector<QPair<int, int>> towerPositions;
};

#endif // JSONMAPPER_HPP
