#ifndef MAGICDOOR_H
#define MAGICDOOR_H

/*
#define yellow 0
#define blue 1
#define red 2
#define silver 3
*/

#include "magicwall.h"
#include "../MagicAnimate/magicopen.h"

class MagicDoor : public MagicWall
{
    friend class MagicOpen;

    int color;

public:
    MagicDoor(int, int, int, MagicMap *, int);
    virtual bool move(MagicMap *);
};

#endif // MAGICDOOR_H
