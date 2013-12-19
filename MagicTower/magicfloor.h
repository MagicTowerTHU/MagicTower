#ifndef MAGICFLOOR_H
#define MAGICFLOOR_H

#include "magicdisplayobject.h"

class MagicFloor : public MagicDisplayObject
{
    QPixmap *pix;
    int x, y;

public:
    MagicFloor();
    MagicFloor(int, int);
    virtual void paint(QPainter *);
};

#endif // MAGICFLOOR_H