#include "magicmedicine.h"
#include "../magicmap.h"

#include <QDebug>

MagicMedicine::MagicMedicine(int x, int y, int level, QString name)
    : MagicDisplayObject(x, y, level)
{
    property["label"] = "medicine_" + name;
    appendClass("medicine");
    pix = new QPixmap(":/images/medicine_" + name);
    switch(name.toInt())
    {
    case 1:
        property["health"] = 100;
        break;
    default:
        property["health"] = 200;
        break;
    }
}

MagicMedicine::~MagicMedicine()
{
    delete pix;
}

void MagicMedicine::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicMedicine::move(MagicMap *map)
{
    map->Tom()->property["health"] += property["health"].getInt();
    property["enabled"] = 0;
    qDebug() <<"Tom:"<< map->Tom()->property["attack"].getInt() <<
                         map->Tom()->property["defend"].getInt() <<
                         map->Tom()->property["health"].getInt();
    return runAction(map, true);
}
