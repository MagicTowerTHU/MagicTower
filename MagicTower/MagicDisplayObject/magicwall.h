#ifndef MAGICWALL_H
#define MAGICWALL_H

#include "magicdisplayobject.h"

#include <QPainter>

class MagicWall : public MagicDisplayObject
{
    QPixmap *pix;

public:
    MagicWall(int, int);
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICWALL_H
