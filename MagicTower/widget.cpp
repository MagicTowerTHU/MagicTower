#include "widget.h"
#include "magicmap.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400, 500);
    mMap = new MagicMap();

    mapToLoad = "";
}

MagicMap *Widget::getMap()
{
    return mMap;
}

void Widget::loadMap(QString filename)
{
    mapToLoad = filename;
}

bool loadingFlag = false;

void Widget::animate()
{
    if (loadingFlag)
        return;
    if (!mapToLoad.isEmpty())
    {
        loadingFlag = true;
        mMap->loadMap(new QFile(mapToLoad));
        mapToLoad = "";
        loadingFlag = false;
    }
    else
        repaint();
}

void Widget::paintEvent(QPaintEvent *)
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
