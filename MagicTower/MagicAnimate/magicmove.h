#ifndef MAGICMOVE_H
#define MAGICMOVE_H

#include "magicanimate.h"

class MagicMove : public MagicAnimate
{
    int direction;
    int distance;
    int step;
    MagicDisplayObject *target;
public:
    MagicMove(MagicMap *, int, int, MagicDisplayObject *, int = -1);
    virtual bool paint(QPainter *); // false -> please destroy me.
};

#endif // MAGICMOVE_H
