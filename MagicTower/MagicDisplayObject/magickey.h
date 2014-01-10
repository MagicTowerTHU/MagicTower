#ifndef MAGICKEY_H
#define MAGICKEY_H

#define yellow 0
#define blue 1
#define red 2
#define silver 3

#include "magicinventory.h"

class MagicKey : public MagicInventory
{
    int color;

public:
    MagicKey(int, int, int);
};

#endif // MAGICKEY_H
