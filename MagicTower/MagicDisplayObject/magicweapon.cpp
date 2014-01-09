#include "magicweapon.h"

MagicWeapon::MagicWeapon(int x, int y, QString name)
    : MagicInventory(x, y)
{
    this->name = name;
    property["label"] = "weapon_" + name;
    pix = new QPixmap(":/images/weapon_" + name);
}
