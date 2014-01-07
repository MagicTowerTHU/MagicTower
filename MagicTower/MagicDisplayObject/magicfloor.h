#ifndef MAGICFLOOR_H
#define MAGICFLOOR_H

#include "magicdisplayobject.h"

class MagicFloor : public MagicDisplayObject
{
    QPixmap *pix;

public:
    MagicFloor();
    MagicFloor(int, int);
    virtual void paint(QPainter *);
    virtual void show() = 0;
};

#endif // MAGICFLOOR_H
