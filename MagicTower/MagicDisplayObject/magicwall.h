#ifndef MAGICWALL_H
#define MAGICWALL_H

#include "magicdisplayobject.h"

#include <QPainter>

class MagicWall : public MagicDisplayObject
{

public:
    QPixmap *pix;
    MagicWall(int, int, int, MagicMap *);
    ~MagicWall();
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICWALL_H
