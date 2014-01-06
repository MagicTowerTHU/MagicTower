
#ifndef WIDGET_H
#define WIDGET_H

#include "magicmap.h"

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent);
    void keyPressEvent(QKeyEvent *);
    MagicMap *getMap();

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    int elapsed;
    MagicMap *mMap;
};

#endif
