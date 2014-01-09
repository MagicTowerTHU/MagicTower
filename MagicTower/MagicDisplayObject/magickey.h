#ifndef MAGICKEY_H
#define MAGICKEY_H

#include "magicinventory.h"

class MagicKey : public MagicInventory
{
    int color;

public:
    MagicKey(int, int, int);
};

#endif // MAGICKEY_H
