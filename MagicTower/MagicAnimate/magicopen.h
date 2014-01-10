#ifndef MAGICOPEN_H
#define MAGICOPEN_H

#include "magicanimate.h"
#include "../MagicDisplayObject/magicdoor.h"

class MagicOpen : public MagicAnimate
{
    int direction;
    MagicDoor *target;

public:
    MagicOpen(MagicMap *, int, MagicDoor *, int);
    virtual bool paint(QPainter *); // false -> please destroy me.
};

#endif // MAGICOPEN_H
