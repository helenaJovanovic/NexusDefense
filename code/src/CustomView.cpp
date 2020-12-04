#include <code/include/CustomView.hpp>
#include <code/include/Game.hpp>
#include <QDebug>

CustomView::CustomView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setTransformationAnchor(QGraphicsView::NoAnchor);
}

void CustomView::leaveEvent(QEvent *event) {
    const QRect& windowRect = geometry();
    QPoint mousePosition = QCursor::pos();

    qint32 x = qBound(windowRect.left(), mousePosition.x(), windowRect.right());
    qint32 y = qBound(windowRect.top(), mousePosition.y(), windowRect.bottom());

    if (animatingCameraMovement == false) {
        animatingCameraMovement = true;

        CameraDir cameraDir = CameraDir::NORTH;

        if(x < mousePosition.x()) {
            cameraDir = CameraDir::EAST;
        } else if(x > mousePosition.x()) {
            cameraDir = CameraDir::WEST;
        } else if(y < mousePosition.y()) {
            cameraDir = CameraDir::SOUTH;
        }

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
    else if(event->key() == Qt::Key_Plus) {
        scale(2, 2);
    }
    else if(event->key() == Qt::Key_Minus) {
        scale(0.5, 0.5);
    }

    // Camera controls
    else if(event->key() == Qt::Key_Right) {
        animateCamera(CameraDir::EAST);
    } else if(event->key() == Qt::Key_Left) {
        animateCamera(CameraDir::WEST);
    } else if(event->key() == Qt::Key_Up) {
        animateCamera(CameraDir::NORTH);
    } else if(event->key() == Qt::Key_Down) {
        animateCamera(CameraDir::SOUTH);
    }
}

void CustomView::animateCamera(const CustomView::CameraDir &dir) {
    qreal xCameraOffset = 0;
    qreal yCameraOffset = 0;

    if(dir == CameraDir::EAST) {
        xCameraOffset = offset;
    } else if(dir == CameraDir::WEST) {
        xCameraOffset = -offset;
    } else if(dir == CameraDir::NORTH) {
        yCameraOffset = -offset;
    } else if(dir == CameraDir::SOUTH) {
        yCameraOffset = offset;
    }

    translate(xCameraOffset, yCameraOffset);
}



