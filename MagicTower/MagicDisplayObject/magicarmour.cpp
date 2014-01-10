#include "magicarmour.h"
#include "../magicmap.h"

#include <QDebug>

MagicArmour::MagicArmour(int x, int y, int level, QString name)
    : MagicInventory(x, y, level)
{
    this->name = name;
    property["label"] = "armour_" + name;
    property["class"] = "armour";
    pix = new QPixmap(":/images/armour_" + name);
    switch(name.toInt())
    {
    case 1:
        property["defend"] = 100;
    case 2:
        property["defend"] = 200;
    default:
        property["defent"] = 300;
    }
}

bool MagicArmour::move(MagicMap *map)
{
    if ((map->Tom()->property["defend"] < property["defend"]).isTrue())
    {
        map->Tom()->property["defend"] = property["defend"].getInt();
        qDebug() <<"Tom: "<< map->Tom()->property["attack"].getInt() << ' '<<
                            map->Tom()->property["defend"].getInt() << ' ' <<
                            map->Tom()->property["health"].getInt() << '\n';
    }
    return MagicInventory::move(map);
}
