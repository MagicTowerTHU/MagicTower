#ifndef MAGICKEY_H
#define MAGICKEY_H

#include "magicinventory.h"

class MagicKey : public MagicInventory
{
    int color;

protected:
    virtual QString getLabel();

public:
    MagicKey(int, int, int, MagicMap *, int);
    virtual bool move(MagicMap *);

    static const int yellow, blue, red, silver;
};

#endif // MAGICKEY_H
