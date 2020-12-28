#include <code/include/InterfaceTowerSlot.hpp>
#include <QDebug>
#include <QGraphicsItem>

InterfaceTowerSlot::InterfaceTowerSlot(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{}

void InterfaceTowerSlot::setSlotNum(int num) {
    slotNumber= num;
}

int InterfaceTowerSlot::getSlotNum() {
    return slotNumber;
}

//TODO: display a label with tower information underneath the buttons
void InterfaceTowerSlot::enterEvent(QEvent* event) {

    if(slotNumber == 0){
        setText("100g");
    }
    else if(slotNumber == 1){
        setText("150g");
    }
    else if(slotNumber == 2){
        setText("250g");
    }

    QPushButton::enterEvent(event);
}

void InterfaceTowerSlot::leaveEvent(QEvent* event) {



    if(slotNumber == 0){
        setText("Mg");
    }
    else if(slotNumber == 1){
        setText("Cannon");
    }
    else if(slotNumber == 2){
        setText("Missile");
    }
    QPushButton::leaveEvent(event);
}




//TODO: attach the "&InterfaceTowerSlot::clicked" signal
//      to a slot function for building towers
//TODO: get the map tiles click event from mouseMoveEvent
//      and check if a slot has been clicked


