#ifndef INTERFACETOWERSLOT_HPP
#define INTERFACETOWERSLOT_HPP

#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>

class InterfaceTowerSlot: public QPushButton {
public:
    InterfaceTowerSlot(const QString &text, QWidget *parent = nullptr);
    void setSlotNum(int num);
    int getSlotNum();
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    int slotNumber;
    //Tower* tower;
};

#endif // INTERFACETOWERSLOT_HPP
