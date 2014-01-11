#ifndef MAGICDESTINATION_H
#define MAGICDESTINATION_H

#include "magicfloor.h"

class MagicDestination : public MagicFloor
{
    int from;

public:
    MagicDestination(int, int, int, int);
};

#endif // MAGICDESTINATION_H
