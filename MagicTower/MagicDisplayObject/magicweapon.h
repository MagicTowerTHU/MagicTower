#ifndef MAGICWEAPON_H
#define MAGICWEAPON_H

#include "magicinventory.h"

class MagicWeapon : public MagicInventory
{
    QString name;
public:
    MagicWeapon(int, int, int, QString, MagicMap *);
    virtual bool move(MagicMap *);
};

#endif // MAGICWEAPON_H
