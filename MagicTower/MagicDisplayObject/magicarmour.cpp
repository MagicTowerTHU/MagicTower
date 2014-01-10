#include "magicarmour.h"

MagicArmour::MagicArmour(int x, int y, int level, QString name)
    : MagicInventory(x, y, level)
{
    this->name = name;
    property["label"] = "armour_" + name;
    property["class"] = "armour";
    pix = new QPixmap(":/images/armour_" + name);
}
