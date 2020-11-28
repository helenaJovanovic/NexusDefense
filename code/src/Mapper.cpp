#include <code/include/Mapper.hpp>
#include <iostream>
#include <QDebug>

Mapper::Mapper(QString& path)
    : path(path)
{
}

/*
 * Returns true if sucessfull and false if not
 * Open a text file and load variables line by line
*/
bool Mapper::readFile(){

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    //Opening a text stream from the file
    QTextStream in(&file);

    QString line = in.readLine();
    QStringList fields = line.split(" ");
    tilesX = fields[0].toInt();
    tilesY = fields[1].toInt();

    int tmp;
/*  Read the matrix where:
 *  1 is entry point, but also a road tile
 *  2 is road tile,
 *  3 is towerPosition,
 *  4 is exit point - nexus, but also a road tile
 *  9 is a tile where road turns (it can be a tower spot also)
*/
    for(int j=0; j<tilesY; j++){
        line = in.readLine();
        fields = line.split(" ");

        for(int i=0; i<tilesX; i++){
           tmp = fields[i].toInt();

           if(tmp == 1){
               unitSpawnPointX = i+1;
               unitSpawnPointY = j+1;
               roadToNexus.push_back({i+1, j+1});
           }
           else if(tmp == 4){
               nexusX = i+1;
               nexusY = j+1;
               roadToNexus.push_back({i+1, j+1});
               turningPointRoad.push_back({i+1, j+1});
           }
           else if(tmp == 2){
               roadToNexus.push_back({i+1, j+1});
           }
           else if(tmp == 9){
               roadToNexus.push_back({i+1, j+1});
               turningPointRoad.push_back({i+1, j+1});
               towerPositions.push_back({i+1, j+1});
           }
           else if(tmp == 3){
               towerPositions.push_back({i+1, j+1});
           }
        }
    }

    file.close();
    return true;
}

//Size of one tile in pixels, with respect to current size of of area
//where the map is being drawn (the resolution of the area where map
//is drawn)
QPair<int, int> Mapper::getSizeOfTilePixels(int resX, int resY){
    return {resX/tilesX, resY/tilesY};
}

//Returns the number of tiles in the grid on the x and y
QPair<int, int> Mapper::getTilesNum(){
    return {tilesX, tilesY};
}

//Returns position in grid
//---------------------------------------------------------------------
QPair<int, int> Mapper::getNexusXY(){
    return {nexusX, nexusY};
}

QPair<int, int> Mapper::getUnitSpawnPointXY(){
    return {unitSpawnPointX, unitSpawnPointY};
}

QVector<QPair<int, int>>& Mapper::getRoadTilesXY(){
    return roadToNexus;
}

QVector<QPair<int, int>>& Mapper::getTowerTilesXY(){
    return towerPositions;
}

QVector<QPair<int, int>>& Mapper::getTurningRoadPoint(){
    return turningPointRoad;
}

//Function that takes height, width of where the map is being drawn
//and position of an object.
//It returns the location in pixels of where the tile should be drawn.
QPair<int, int> Mapper::gridPosToPixels(int resX, int resY, QPair<int, int> gridPos){
    return{(gridPos.first-1)*(resX/tilesX), (gridPos.second-1)*(resY/tilesY)};
}

//Return unit path that returns QPointF vector
//with points where a unit must turn
//--->The pixels returned are positioned in the middle of the tile
QVector<QPointF>& Mapper::getUnitTurnPointsXY(int resX, int resY){
    QPointF point;
    QPointF point_old;
    int n = turningPointRoad.size();

    QPair<int, int> tileSize = getSizeOfTilePixels(resX, resY);
    float sizeOfHalfTileX = tileSize.first/2;
    float sizeOfHalfTileY = tileSize.first/2;

    QPair<int, int> temp = gridPosToPixels(resX, resY, getUnitSpawnPointXY());
    point.setX(static_cast<float>(temp.first) + sizeOfHalfTileX);
    point.setY(static_cast<float>(temp.second) + sizeOfHalfTileY);

    //Go through all turning tiles
    for(int i=0; i<n; i++){
        //Get the pixel X,Y of tile
        temp = gridPosToPixels(resX, resY, turningPointRoad[i]);

        //Save old point
        point_old = point;

        //Add half of tile size to it, to get the center of the tile
        point.setX(static_cast<float>(temp.first) + sizeOfHalfTileX);
        point.setY(static_cast<float>(temp.second) + sizeOfHalfTileY);

        turningPointFs.push_back(point);
        directions.push_back(calcDirection(point_old, point));
    }

    return turningPointFs;
}

//Calculate direction using two points
unsigned Mapper::calcDirection(QPointF p1, QPointF p2){
    //go down
    if(p1.x() == p2.x() && p1.y() < p2.y()){
        return 1u;
    }
    //go left
    else if(p1.x() > p2.x() && p1.y() == p2.y()){
        return 2u;
    }
    //go right
    else if(p1.x() < p2.x() && p1.y() == p2.y()){
        return 3u;
    }

    return 4u;
}

//Next we want the direction where to which
//the unit must turn from that point

//For each index in the unitTurnPoint vector
//there is a corresponding direction in this vector
QVector<unsigned>& Mapper::getDirections(){
    return directions;
}

Mapper::~Mapper(){}
