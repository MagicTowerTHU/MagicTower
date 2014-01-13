#include "magicarmour.h"
#include "../magicmap.h"

#include <QDebug>

MagicArmour::MagicArmour(int x, int y, int level, QString name, MagicMap *parent)
    : MagicInventory(x, y, level, parent)
{
    this->name = name;
    property["label"] = "armour_" + name;
    appendClass("armour");
    pix = new QPixmap(":/images/armour_" + name);
    switch(name.toInt())
    {
    case 1:
        property["defend"] = 100;
        break;
    case 2:
        property["defend"] = 200;
        break;
    default:
        property["defend"] = 300;
        break;
    }
}

bool MagicArmour::move(MagicMap *map)
{
    map->Tom()->property["defend"] += property["defend"].getInt();
    /*qDebug() <<"Tom:"<< map->Tom()->property["attack"].getInt() <<
                         map->Tom()->property["defend"].getInt() <<
                         map->Tom()->property["health"].getInt();*/
    return MagicInventory::move(map);
}
