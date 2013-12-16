#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

class MagicTom : public MagicDisplayObject
{
    QPixmap *pix;
    int x, y;
    int dx, dy;

public:
    MagicTom();
    virtual void paint(QPainter *painter);
    void moveTo(int, int);
    void setStep(int, int);
    void move();
};

#endif // MAGICTOM_H
