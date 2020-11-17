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

    //Read integer variables
    for(int i=0; i<6; i++){
        //Read line by line for first 6 lines and seperate with :
        QString line = in.readLine();
        QStringList fields = line.split(" : ");

        switch (i) {
            //Loading first six values into variables
            case 0: tilesX = fields[1].toInt(); break;
            case 1: tilesY = fields[1].toInt(); break;
            case 2: nexusX = fields[1].toInt(); break;
            case 3: nexusY = fields[1].toInt(); break;
            case 4: unitSpawnPointX = fields[1].toInt(); break;
            case 5: unitSpawnPointY = fields[1].toInt(); break;
        default: break;
        }
    }


    //Read arrays defined like poslist : [x1, y1], [x2, y2]
    QString line = in.readLine();
    loadArrayString(line, roadToNexus);

    line = in.readLine();
    loadArrayString(line, towerPositions);



    file.close();
    return true;
}

/*
 * Operations with string in array format
 * Load values from such string into QVector<QPair<int, int>> type
*/
void Mapper::loadArrayString(QString& line, QVector<QPair<int, int>> &obj){

        //Remove from list from string in format name : list
        QStringList fields = line.split(" : ");
        //Split a list in format [x1, y1], [x2, y2] ... with a serperator ", "
        QString test = fields[1];

        fields = fields[1].split("], [");

        //Go through [xi, yi] format strings and remove [ and ] from start and end
        //Then split by ", " and transform two numbers to integers
        //So that they could be put into a vector in pair form
        for(QString& str : fields){

            QString tmp = str;
            int n = tmp.size();
            if(tmp[0] == '['){
                tmp.remove(0, 1);
            }
            else if(tmp[n-1] == ']'){
                tmp.remove(n-1, 1);
            }

            QStringList nums = tmp.split(", ");
            obj.push_back({nums[0].toInt(), nums[1].toInt()});
        }

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

//Function that takes height, width of where the map is being drawn
//and position of an object.
//It returns the location in pixels of where the tile should be drawn.
QPair<int, int> Mapper::gridPosToPixels(int resX, int resY, QPair<int, int> gridPos){
    return{(gridPos.first-1)*(resX/tilesX), (gridPos.second-1)*(resY/tilesY)};
}
