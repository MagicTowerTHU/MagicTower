#include "widget.h"
#include "magictom.h"
#include "helper.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(500, 500);
    tom = new MagicTom();
}

void Widget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //helper->paint(&painter, event, elapsed);
    tom->paint(&painter);
    painter.end();
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Left:
        tom->move(-3, 0);
        break;
    case Qt::Key_Up:
        tom->move(0, -3);
        break;
    case Qt::Key_Right:
        tom->move(3, 0);
        break;
    case Qt::Key_Down:
        tom->move(0, 3);
        break;
    }
}
