#ifndef MAGICTELEPORT_H
#define MAGICTELEPORT_H

#include "magicinventory.h"

class MagicTeleport : public MagicInventory
{

public:
    MagicTeleport(int, int, int, MagicMap *);
    virtual bool move(MagicMap *);
};

#endif // MAGICTELEPORT_H
