#ifndef SPRITELOADER_HPP
#define SPRITELOADER_HPP

#include "Sprite.hpp"

#include <QString>


class SpriteLoader {
public:
    // Takes the paths to folders containing json defintions for each type
    // (misc is for anything that needs animation, but isn't a unit or tower)
    SpriteLoader(
        const QString& unitsFolderPath,
        const QString& towersFolderPath,
        const QString& miscFolderPath
    );

    Sprite* getTowerSprite(const QString&);
    Sprite* getUnitSprite(const QString&);
    Sprite* getMiscSprite(const QString&);

private:
    QMap<QString, Sprite*> parseAndLoadSprites(const QString& folderPath);
    Sprite* parseSprite(const QString& filePath);

    QMap<QString, Sprite*> unitSprites;
    QMap<QString, Sprite*> towerSprites;
    QMap<QString, Sprite*> miscSprites;
};

#endif // SPRITELOADER_HPP
