#ifndef MAGICWEAPON_H
#define MAGICWEAPON_H

#include "magicinventory.h"

class MagicWeapon : public MagicInventory
{
    QString name;
public:
    MagicWeapon(int, int, QString);
};

#endif // MAGICWEAPON_H
