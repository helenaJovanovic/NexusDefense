QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    code/src/CustomView.cpp \
    code/src/EnemyUnit.cpp \
    code/src/GameScore.cpp \
    code/src/Gold.cpp \
    code/src/Health.cpp \
    code/src/IngameInterface.cpp \
    code/src/InterfaceTowerSlot.cpp \
    code/src/Projectile.cpp \
    code/src/Sprite.cpp \
    code/src/SpriteLoader.cpp \
    code/src/Tower.cpp \
    code/src/Turret.cpp \
    code/src/GameTimer.cpp \
    code/src/Game.cpp \
    code/src/Map.cpp \
    code/src/MapTile.cpp \
    code/src/Mapper.cpp \
    code/src/main.cpp

HEADERS += \
    code/include/CustomView.hpp \
    code/include/EnemyUnit.hpp \
    code/include/GameScore.hpp \
    code/include/Gold.hpp \
    code/include/Health.hpp \
    code/include/IngameInterface.hpp \
    code/include/InterfaceTowerSlot.hpp \
    code/include/Projectile.hpp \
    code/include/Sprite.hpp \
    code/include/SpriteLoader.hpp \
    code/include/Tower.hpp \
    code/include/Turret.hpp \
    code/include/GameTimer.hpp \
    code/include/Game.hpp \
    code/include/Map.hpp \
    code/include/MapTile.hpp \
    code/include/Mapper.hpp


INCLUDEPATH = libraries/boost_1_74_0/

#FORMS +=



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc


DISTFILES += \
    resources/mapPrototype.txt


