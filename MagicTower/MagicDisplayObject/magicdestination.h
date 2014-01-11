#ifndef MAGICDESTINATION_H
#define MAGICDESTINATION_H

#include "magicfloor.h"

class MagicDestination : public MagicFloor
{
    int from;

public:
    MagicDestination(int, int, int, int, MagicMap *);
};

#endif // MAGICDESTINATION_H
