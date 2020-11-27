#include <code/include/SpriteLoader.hpp>
/*#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>*/

#include <QDirIterator>
#include <QDebug>

//namespace pt = boost::property_tree

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
    QString name;
    qDebug() << "Currently parsing: " << filePath;
    return new Sprite(name);
}
