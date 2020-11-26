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
