
#ifndef WIDGET_H
#define WIDGET_H

#include "magictom.h"

#include <QWidget>

class Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent);
    void keyPressEvent(QKeyEvent *);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Helper *helper;
    int elapsed;
    MagicTom *tom;
};

#endif
