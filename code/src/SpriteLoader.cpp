#include <code/include/SpriteLoader.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <QDirIterator>
#include <QDebug>
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

    // TODO: use boost to parse through json files and
    // create a Sprite object based on the info in the file
    QString name = QString::fromStdString(tree.get("name", ""));
    QString initialState = QString::fromStdString(tree.get("spriteAnimation.initialState", ""));

    qDebug() << name << ", initial state: " << initialState;

    return new Sprite(name);
}
