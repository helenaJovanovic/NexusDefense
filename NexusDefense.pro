QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    code/src/Game.cpp \
    code/src/Map.cpp \
    code/src/MapTile.cpp \
    code/src/Mapper.cpp \
    code/src/main.cpp

HEADERS += \
    code/include/Game.hpp \
    code/include/Map.hpp \
    code/include/MapTile.hpp \
    code/include/Mapper.hpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc \
    resources/res.qrc

DISTFILES += \
    resources/mapPrototype.txt
