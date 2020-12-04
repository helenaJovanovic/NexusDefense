#include <code/include/CustomView.hpp>
#include <code/include/Game.hpp>
#include <QDebug>

CustomView::CustomView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{}

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
    if(event->key() == Qt::Key_Escape) {
        Game::game().getGameApp()->quit();
    }
}
