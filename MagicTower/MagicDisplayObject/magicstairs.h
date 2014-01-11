#ifndef MAGICSTAIRS_H
#define MAGICSTAIRS_H

#include "magicfloor.h"

class MagicStairs : public MagicFloor
{
    int direction; //only 1 and -1 are allowed

public:
    MagicStairs(int, int, int, MagicMap *, int);
    virtual bool move(MagicMap *);
};

#endif // MAGICSTAIRS_H
