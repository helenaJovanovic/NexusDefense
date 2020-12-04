#include <code/include/CustomView.hpp>
#include <code/include/Game.hpp>
#include <QDebug>

CustomView::CustomView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setTransformationAnchor(QGraphicsView::NoAnchor);
}

void CustomView::enableMouseMovement(){
    cameraEnabled = true;
}

void CustomView::leaveEvent(QEvent *event) {
    const QRect& windowRect = geometry();
    QPoint mousePosition = QCursor::pos();

    qint32 x = qBound(windowRect.left(), mousePosition.x(), windowRect.right());
    qint32 y = qBound(windowRect.top(), mousePosition.y(), windowRect.bottom());

    if(cameraEnabled) {
        CameraDir cameraDir = CameraDir::NORTH;
        if(x < mousePosition.x()) {
            cameraDir = CameraDir::EAST;
        } else if(x > mousePosition.x()) {
            cameraDir = CameraDir::WEST;
        } else if(y < mousePosition.y()) {
            cameraDir = CameraDir::SOUTH;
        }
        if(!animatingCameraMovement)
            animateCamera(cameraDir);
    }

    if(x != mousePosition.x() || y != mousePosition.y())
        QCursor::setPos(x, y);

    event->accept();
    QGraphicsView::leaveEvent(event);
}

void CustomView::keyPressEvent(QKeyEvent *event) {
    // Options window (quits the game atm)
    if(event->key() == Qt::Key_Escape) {
        Game::game().getGameApp()->quit();
    }

    // Zoom controls
    // TODO: animate this, and add it to mouseWheel event aswell
    else if(event->key() == Qt::Key_Plus) {
        scale(2, 2);
    }
    else if(event->key() == Qt::Key_Minus) {
        scale(0.5, 0.5);
    }

    // Camera controls
    else
        if(cameraEnabled) {
            if(event->key() == Qt::Key_Right) {
                animateCamera(CameraDir::EAST);
            } else if(event->key() == Qt::Key_Left) {
                animateCamera(CameraDir::WEST);
            } else if(event->key() == Qt::Key_Up) {
                animateCamera(CameraDir::NORTH);
            } else if(event->key() == Qt::Key_Down) {
                animateCamera(CameraDir::SOUTH);
            }
        }
}

void CustomView::animateCamera(const CustomView::CameraDir &dir) {
    if(animatingCameraMovement)
        return;

    if(dir == CameraDir::EAST) {
        yOffset = 0;
        xOffset = defaultOffset;
    } else if(dir == CameraDir::WEST) {
        xOffset = -defaultOffset;
        yOffset = 0;
    } else if(dir == CameraDir::NORTH) {
        yOffset = -defaultOffset;
        xOffset = 0;
    } else if(dir == CameraDir::SOUTH) {
        yOffset = defaultOffset;
        xOffset = 0;
    }

    if(!animatingCameraMovement)
        connect(Game::game().gameTimer, SIGNAL(timeTickSignal()), this, SLOT(cameraMoveTick()));
}

void CustomView::cameraMoveTick() {
    timeElapsed += 16;
    translate(-xOffset, -yOffset);
    if(timeElapsed >= 160) {
        disconnect(Game::game().gameTimer, SIGNAL(timeTickSignal()), this, SLOT(cameraMoveTick()));
        timeElapsed = 0;
        animatingCameraMovement = false;
    }
}



