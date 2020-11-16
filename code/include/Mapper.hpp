#ifndef JSONMAPPER_HPP
#define JSONMAPPER_HPP

#include <QFile>
#include <QString>


class Mapper
{
public:
    //Required: Path to map .txt file, resX, resY of screen
    Mapper(QString& path, int resolutionX, int resolutionY);

    //Returns true if file is opened succesfully
    bool readFile();
    //Enables easy reading of lines in format of
    // poslist : [x1, y1], [x2, y2]
    //with ", " being a seperator
    void loadArrayString(QString& line, QVector<QPair<int, int>> &obj);

    //Size of one tile in pixels
    int getPixelSizeTileX();
    int getPixelSizeTileY();

    //Amount of tiles in the grid in x and y coord
    QPair<int, int> getTilesXY();

    //These return upper left starting positions of game objects, in pixels
    //---------------------------------------------------------------------
    QPair<int, int> getNexusXY();
    QPair<int, int> getUnitSpawnPointXY();
    QVector<QPair<int, int>>& getRoadTilesXY();
    QVector<QPair<int, int>>& getTowerTilesXY();

private:
    //---------------
    //Screen resolution
    int resolutionX;
    int resolutionY;
    //----------------

    int pixelWidthTile;
    int pixelHeightTile;

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
