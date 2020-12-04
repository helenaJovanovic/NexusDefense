#ifndef CUSTOMVIEW_HPP
#define CUSTOMVIEW_HPP

#include <QGraphicsView>
#include <QEvent>
#include <QKeyEvent>

class CustomView: public QGraphicsView {
public:
    CustomView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // CUSTOMVIEW_HPP
