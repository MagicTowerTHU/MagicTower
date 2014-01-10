#include "magicweapon.h"

MagicWeapon::MagicWeapon(int x, int y, int level, QString name)
    : MagicInventory(x, y, level)
{
    this->name = name;
    property["label"] = "weapon_" + name;
    property["class"] = "weapon";
    pix = new QPixmap(":/images/weapon_" + name);
}
