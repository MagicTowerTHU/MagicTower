#include "magicmedicine.h"
#include "../magicmap.h"

#include <QDebug>

MagicMedicine::MagicMedicine(int x, int y, int level, QString name, MagicMap *parent)
    : MagicDisplayObject(x, y, level, parent)
{
    property["label"] = "medicine_" + name;
    appendClass("medicine");
    pix = new QPixmap(":/images/medicine_" + name);
    switch(name.toInt())
    {
    case 1:
        property["health"] = 100;
        break;
    case 2:
        property["health"] = 200;
        break;
    case 3:
        property["attack"] = 200;
        break;
    case 4:
        property["defend"] = 200;
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
    if (property["label"].getString() == "medicine_1" || property["label"].getString() == "medicine_2")
        map->Tom()->property["health"] += property["health"].getInt();
    else if (property["label"].getString() == "medicine_3")
        map->Tom()->property["attack"] += property["attack"].getInt();
    else
        map->Tom()->property["defend"] += property["defend"].getInt();

    property["enabled"] = 0;
    qDebug() <<"Tom:"<< map->Tom()->property["attack"].getInt() <<
                         map->Tom()->property["defend"].getInt() <<
                         map->Tom()->property["health"].getInt();
    return runAction(map, true);
}
