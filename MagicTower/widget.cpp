#include "widget.h"
#include "magicmap.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    elapsed = 0;
    setFixedSize(500, 500);
    mMap = new MagicMap();
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
    mMap->paint(&painter);
    painter.end();
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    mMap->keyPressEvent(e);
}
