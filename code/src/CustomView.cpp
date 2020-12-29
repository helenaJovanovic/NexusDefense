#include <code/include/CustomView.hpp>
#include <code/include/Game.hpp>
#include <QDebug>
#include <QScrollBar>

CustomView::CustomView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //showFullScreen();
}

void CustomView::enableMouseMovement(){
    cameraEnabled = true;
    connect(Game::game().gameTimer, &QTimer::timeout, this, &CustomView::cameraMoveTick);
}

void CustomView::mouseMoveEvent(QMouseEvent* event) {
    if(!cameraEnabled) return;

    const QRect& windowRect = geometry();
    qint32 mouseXPos = event->x();
    qint32 mouseYPos = event->y();

    qint32 cameraEdgeOffset = Game::game().tileWidth*2;
    qint32 right = windowRect.width();
    qint32 bottom = windowRect.height();

    if(!animatingCameraMovement) {
        if(mouseXPos >= right-cameraEdgeOffset) {
            animateCamera(CameraDir::EAST);
        } else if (mouseXPos <= 0+cameraEdgeOffset) {
            animateCamera(CameraDir::WEST);
        } else if (mouseYPos <= 0+cameraEdgeOffset) {
            animateCamera(CameraDir::NORTH);
        } else if (mouseYPos >= bottom-cameraEdgeOffset) {
            animateCamera(CameraDir::SOUTH);
        }
    } else {
        if(mouseXPos <= right-cameraEdgeOffset &&
           mouseXPos >= 0+cameraEdgeOffset &&
           mouseYPos >= 0+cameraEdgeOffset &&
           mouseYPos <= bottom-cameraEdgeOffset) {
            animatingCameraMovement = false;
        }
    }

    event->accept();
    QGraphicsView::mouseMoveEvent(event);
}

void CustomView::leaveEvent(QEvent *event) {
    const QRect& windowRect = geometry();
    QPoint mousePosition = QCursor::pos();

    qint32 x = qBound(windowRect.left(), mousePosition.x(), windowRect.right());
    qint32 y = qBound(windowRect.top(), mousePosition.y(), windowRect.bottom());

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

        scaleScores(0.5);
         adjustScores();

    }
    else if(event->key() == Qt::Key_Minus) {
        scale(0.5, 0.5);

        scaleScores(2);
         adjustScores();
    }

    else if(event->key() == Qt::Key_1) {
        Game::game().setTower1();
    }

    else if(event->key() == Qt::Key_2) {
        Game::game().setTower2();
    }

    else if(event->key() == Qt::Key_3) {
        Game::game().setTower3();
    }

    // Camera controls
    else
        if(!animatingCameraMovement && cameraEnabled) {
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

void CustomView::keyReleaseEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_Right ||
       event->key() == Qt::Key_Left ||
       event->key() == Qt::Key_Up ||
       event->key() == Qt::Key_Down) {

       animatingCameraMovement = false;
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




    animatingCameraMovement = true;
}

void CustomView::cameraMoveTick() {
    if(!animatingCameraMovement) return;

    translate(-xOffset, -yOffset);


    //Jako ratchet resenje da fiksiram poene gde treba
    //Bez da menjam klasu koju je neko vec uradio
    //bozemiteprosti
    adjustScores();


    /*horizontalScrollBar()->setValue( horizontalScrollBar()->value() + xOffset);
    verticalScrollBar()->setValue( verticalScrollBar()->value() + yOffset);*/
}

//When camera moves move the scores so that they are always on top right
void CustomView::adjustScores(){
    QPointF pos = this->mapToScene(0, 0);
    qreal currScale = Game::game().health->scale();
    Game::game().gold->setPos(pos.x(), pos.y());
    Game::game().health->setPos(pos.x(), pos.y()+(20*currScale));
    Game::game().score->setPos(pos.x(), pos.y()+ (40*currScale));
}

//If theres is a zoom then set scaling of scores
void CustomView::scaleScores(qreal x){
    Game::game().health->setScale(
                Game::game().health->scale()*x
                );
    Game::game().score->setScale(
                Game::game().score->scale()*x
                );
    Game::game().gold->setScale(
                Game::game().gold->scale()*x
                );

}
