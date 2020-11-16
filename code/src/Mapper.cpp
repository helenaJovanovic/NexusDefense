#include <code/include/Mapper.hpp>
#include <iostream>
#include <QDebug>

Mapper::Mapper(QString& path, int resolutionX, int resolutionY)
    : resolutionX(resolutionX), resolutionY(resolutionY), path(path)
{
}

/*Returns true if sucessfull and false if not
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

    //Now we can calculate pixel size of one tile
    pixelWidthTile = resolutionX/tilesX;
    pixelHeightTile = resolutionY/tilesY;

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
            obj.push_back({(nums[0].toInt()-1)*pixelWidthTile, (nums[1].toInt()-1)*pixelWidthTile});
        }

}

//Returns width of one tile in pixels
int Mapper::getPixelSizeTileX(){
    return pixelWidthTile;
}

//Returns hieght of one tile in pixels
int Mapper::getPixelSizeTileY(){
    return pixelHeightTile;
}

//Returns the number of tiles in the grid on the x and y
QPair<int, int> Mapper::getTilesXY(){
    return {tilesX, tilesY};
}

//These return upper left starting positions of game objects, in pixels
//---------------------------------------------------------------------
QPair<int, int> Mapper::getNexusXY(){
    return {(nexusX-1)*pixelWidthTile, (nexusY-1)*pixelHeightTile};
}

QPair<int, int> Mapper::getUnitSpawnPointXY(){
    return {(unitSpawnPointX-1)*pixelWidthTile, (unitSpawnPointY-1)*pixelHeightTile};
}

QVector<QPair<int, int>>& Mapper::getRoadTilesXY(){
    return roadToNexus;
}

QVector<QPair<int, int>>& Mapper::getTowerTilesXY(){
    return towerPositions;
}
