#include "magicweapon.h"

#include <QDebug>

MagicWeapon::MagicWeapon(int x, int y, int level, QString name)
    : MagicInventory(x, y, level)
{
    this->name = name;
    property["label"] = "weapon_" + name;
    appendClass("weapon");
    pix = new QPixmap(":/images/weapon_" + name);
    switch(name.toInt())
    {
    case 1:
        property["attack"] = 100;
        break;
    case 2:
        property["attack"] = 200;
        break;
    default:
        property["attack"] = 300;
        break;
    }
}

bool MagicWeapon::move(MagicMap *map)
{
    map->Tom()->property["attack"] += property["attack"].getInt();
    qDebug() <<"Tom: "<< map->Tom()->property["attack"].getInt() << ' '<<
                         map->Tom()->property["defend"].getInt() << ' ' <<
                         map->Tom()->property["health"].getInt() << '\n';
    return MagicInventory::move(map);
}
