#include <code/include/TextItem.hpp>
#include <QFont>

TextItem::TextItem()
{
    setPlainText("hello world");
    QFont f;
    f.setPointSize(20);
    f.setBold(true);
    f.setFamily("Helvetica");
    setFont(f);

    setFlags(QGraphicsItem::ItemIsMovable    |
             QGraphicsItem::ItemIsFocusable  |
             QGraphicsItem::ItemIsSelectable);
    setTextInteractionFlags(Qt::NoTextInteraction);

}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QGraphicsTextItem::paint(painter, option, widget);
}

void TextItem::focusOutEvent(QFocusEvent *event)
{
  Q_UNUSED(event);
  setTextInteractionFlags(Qt::NoTextInteraction);
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setTextInteractionFlags(Qt::TextEditable);
    setFocus();
}
