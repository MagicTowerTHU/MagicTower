#ifndef MAGICOPEN_H
#define MAGICOPEN_H

#include "magicanimate.h"

class MagicDoor;

class MagicOpen : public MagicAnimate
{
    int direction;
    MagicDoor *target;

public:
    MagicOpen(MagicMap *, MagicDoor *);
    virtual bool paint(QPainter *); // false -> please destroy me.
};

#endif // MAGICOPEN_H
