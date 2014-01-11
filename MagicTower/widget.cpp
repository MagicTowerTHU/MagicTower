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
    recToLoad = "";
    recToSave = "";
}

MagicMap *Widget::getMap()
{
    return mMap;
}

void Widget::saveRec(QString filename)
{
    recToSave = filename;
}

void Widget::loadRec(QString filename)
{
    recToLoad = filename;
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
    if (!recToLoad.isEmpty())
    {
        loadingFlag = true;
        mMap->loadRecord(new QFile(recToLoad));
        recToLoad = "";
        loadingFlag = false;
    }
    if (!recToSave.isEmpty())
    {
        loadingFlag = true;
        mMap->saveRecord(new QFile(recToSave));
        recToSave = "";
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
