#ifndef CUSTOMVIEW_HPP
#define CUSTOMVIEW_HPP

#include <QGraphicsView>
#include <QEvent>
#include <QKeyEvent>
#include <QTimeLine>

class CustomView: public QGraphicsView {
public:
    CustomView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QTimeLine cameraMoveTimeline;

    bool animatingCameraMovement = false;
    qreal offset = 16;
    enum CameraDir{
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    void animateCamera(const CameraDir& dir);
};

#endif // CUSTOMVIEW_HPP
