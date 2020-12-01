#include <code/include/SpriteLoader.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <QDirIterator>
#include <QDebug>
#include <QVector>
#include <iostream>
#include <sstream>


namespace pt = boost::property_tree;

SpriteLoader::SpriteLoader(
    const QString &unitsFolderPath,
    const QString &towersFolderPath,
    const QString &miscFolderPath = ""
) {
    unitSprites = parseAndLoadSprites(unitsFolderPath);
    towerSprites = parseAndLoadSprites(towersFolderPath);
    if(miscFolderPath != "")
        miscSprites = parseAndLoadSprites(miscFolderPath);
}

SpriteLoader::~SpriteLoader() {
    for(auto sprite: unitSprites.values()) {
        delete sprite;
    }
    qDebug() << "Deleted allocated sprites.";
}

Sprite *SpriteLoader::getUnitSprite(const QString & name) {
    return unitSprites[name];
}

QMap<QString, Sprite*> SpriteLoader::parseAndLoadSprites(const QString& path) {
    QMap<QString, Sprite*> result;

    QDirIterator it(QString(":/" + path), QDirIterator::Subdirectories);
    while(it.hasNext()) {
        it.next();
        Sprite *parsedSprite = parseSprite(it.filePath());
        result.insert(parsedSprite->getName(), parsedSprite);
    }

    return result;
}

Sprite *SpriteLoader::parseSprite(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::exception();
    QTextStream in(&file);

    std::stringstream ss;
    ss << in.readAll().toStdString();

    pt::ptree tree;
    pt::read_json(ss, tree);


    QString name = QString::fromStdString(tree.get("name", ""));
    QString initialState = QString::fromStdString(tree.get("spriteAnimation.initialState", ""));
    QString spritesheet = QString::fromStdString(tree.get("spritesheet", ""));

    Sprite* resultingSprite = new Sprite(name, spritesheet, initialState);

    for(auto &state: tree.get_child("spriteAnimation.states")) {
        // name of the state
        QString stateName = QString::fromStdString(state.second.get("stateName", ""));
        QVector<Sprite::frame> frameVector;

        std::vector<int> tmpVector;
        for(auto &frame: state.second.get_child("stateFrames")) {
            // duration in ms of the frame
            int duration = stoi( frame.second.get("duration", "") );

            for(auto &origin: frame.second.get_child("origin")) {
                tmpVector.push_back(origin.second.get_value(0));
            }

            // origin
            QPoint originPoint(tmpVector[0], tmpVector[1]);

            tmpVector.clear();
            for(auto &rect: frame.second.get_child("rect")) {
                tmpVector.push_back(rect.second.get_value(0));
            }

            // rectangle (first 2 coords are top left point,
            // last 2 are bottom right point)

            // careful with y axis, Rect uses qt coord system
            QRect frameRect(
                QPoint(tmpVector[0], tmpVector[1]),
                QPoint(tmpVector[2], tmpVector[3])
            );

            tmpVector.clear();

            Sprite::frame stateFrame;
            stateFrame.duration = duration;
            stateFrame.origin = originPoint;
            stateFrame.rect = frameRect;
            frameVector.push_back(stateFrame);
        }

        resultingSprite->animationStates[stateName] = frameVector;
    }


    return resultingSprite;
}
