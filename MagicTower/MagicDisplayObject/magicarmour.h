#ifndef MAGICARMOUR_H
#define MAGICARMOUR_H

#include "magicinventory.h"

class MagicArmour : public MagicInventory
{
    QString name;
public:
    MagicArmour(int, int, int, QString);
    virtual bool move(MagicMap *);
};

#endif // MAGICARMOUR_H
