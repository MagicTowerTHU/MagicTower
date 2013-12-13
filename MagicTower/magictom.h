#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

class MagicTom : public MagicDisplayObject
{
    QPixmap *pix;
    double x, y;

public:
    MagicTom();
    virtual void paint(QPainter *painter);
    void move(double, double);
};

#endif // MAGICTOM_H
