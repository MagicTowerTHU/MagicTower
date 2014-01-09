#include "magicarmour.h"

MagicArmour::MagicArmour(int x, int y, QString name)
    : MagicInventory(x, y)
{
    this->name = name;
    property["label"] = "armour_" + name;
    pix = new QPixmap(":/images/armour_" + name);
}
