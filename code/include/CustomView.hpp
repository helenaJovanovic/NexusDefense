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
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    virtual void wheelEvent ( QWheelEvent * event ) override
    {
        //Ignore scrolling because we want mouse movement
        //To control camera
        event->ignore();
    }

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

    //Adjust scores to movement and scaling
    void adjustScores();
    void scaleScores(qreal x);

private slots:
    void cameraMoveTick();
signals:
    void EnterIsPressed();


};

#endif // CUSTOMVIEW_HPP
