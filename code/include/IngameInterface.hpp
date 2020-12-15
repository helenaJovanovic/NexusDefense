#ifndef INGAMEINTERFACE_HPP
#define INGAMEINTERFACE_HPP

#include "CustomView.hpp"
#include "InterfaceTowerSlot.hpp"

#include <QPushButton>


class IngameInterface {
public:
    IngameInterface(CustomView* view);
    ~IngameInterface();
    void showInterface();
    void hideInterface();
private:
    QVector<InterfaceTowerSlot*> towerSlots;
};

#endif // INGAMEINTERFACE_HPP
