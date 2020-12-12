#ifndef CUSTOMVIEW_HPP
#define CUSTOMVIEW_HPP

#include <QGraphicsView>
#include <QEvent>
#include <QKeyEvent>

class CustomView: public QGraphicsView {
    Q_OBJECT

public:
    CustomView(QGraphicsScene *scene, QWidget *parent = nullptr);
    void enableMouseMovement();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    bool cameraEnabled = false;
    bool animatingCameraMovement = false;
    qreal defaultOffset = 8;
    qreal xOffset;
    qreal yOffset;
    qint32 timeElapsed = 0;
    enum CameraDir{
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    void animateCamera(const CameraDir& dir);

private slots:
    void cameraMoveTick();
};

#endif // CUSTOMVIEW_HPP
