#ifndef MAGICWALL_H
#define MAGICWALL_H

#include "magicdisplayobject.h"

#include <QPainter>

class MagicWall : public MagicDisplayObject
{
    QPixmap *pix;

public:
    MagicWall();
    virtual void paint(QPainter *);
};

#endif // MAGICWALL_H
