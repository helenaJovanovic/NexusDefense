#include <code/include/IngameInterface.hpp>
#include <code/include/Game.hpp>
#include <QObject>

IngameInterface::IngameInterface(CustomView* view) {
    for(int i=0; i<4; i++) {




        towerSlots.append(new InterfaceTowerSlot("T", view));
        towerSlots[i]->setSlotNum(i);
        towerSlots[i]->setGeometry(QRect(QPoint(view->width()-5*64+64*(i+1)-4, 4), QSize(64, 64)));
        towerSlots[i]->setStyleSheet(
            "QPushButton {"
                "border-image:url(:/images/images/normal.png);"
                "min-width: 64;"
                "min-height: 64;"
                "font: 20px Arial, sans-serif;"
            "}"
            "QPushButton:pressed {"
                "border-image:url(:/images/images/pressed.png);"
                "min-width: 64;"
                "min-height: 64;"
            "}"
        );

        switch (i) {
        case 0:
            QObject::connect(towerSlots[i], SIGNAL(released()), &Game::game(), SLOT(setTower1())); break;
        case 1:
            QObject::connect(towerSlots[i], SIGNAL(released()), &Game::game(), SLOT(setTower2())); break;
        case 2:
            QObject::connect(towerSlots[i], SIGNAL(released()), &Game::game(), SLOT(setTower3())); break;
        case 3:
            QObject::connect(towerSlots[i], SIGNAL(released()), &Game::game(), SLOT(setTower4())); break;
        default:
            break;
        }


    }


}

void IngameInterface::showInterface() {
    for(auto &p: towerSlots) {
        p->show();
    }
}

void IngameInterface::hideInterface() {
    for(auto &p: towerSlots) {
        p->hide();
    }
}
