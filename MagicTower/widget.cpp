#include "widget.h"
#include "magicmap.h"
#include "helper.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
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
    //helper->paint(&painter, event, elapsed);
    mMap->paint(&painter);
    painter.end();
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    mMap->keyPressEvent(e);
}
