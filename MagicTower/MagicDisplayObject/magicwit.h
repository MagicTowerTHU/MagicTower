#ifndef MAGICWIT_H
#define MAGICWIT_H

#include "magicinventory.h"

class MagicWit : public MagicInventory
{
public:
    MagicWit(int, int, int, MagicMap *);
    virtual bool move(MagicMap *);
};

#endif // MAGICWIT_H
