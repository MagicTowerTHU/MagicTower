#include "magicenemy.h"

#include <QPainter>

MagicEnemy::MagicEnemy(int x, int y, int level, QString name)
    : MagicDisplayObject(x, y, level)
{
    property["label"] = "enemy_" + name;
    property["class"] = "enemy";
    pix[0] = new QPixmap(":/images/enemy_" + name + ".0");
    pix[1] = new QPixmap(":/images/enemy_" + name + ".1");
    switch(name.toInt())
    {
    case 1:
        property["attack"] = 10;
        property["defend"] = 10;
        property["health"] = 100;
    case 2:
        property["attack"] = 10;
        property["defend"] = 10;
        property["health"] = 100;
    case 3:
        property["attack"] = 10;
        property["defend"] = 10;
        property["health"] = 100;
    case 4:
        property["attack"] = 10;
        property["defend"] = 10;
        property["health"] = 100;
    case 5:
        property["attack"] = 10;
        property["defend"] = 10;
        property["health"] = 100;
    case 6:
        property["attack"] = 10;
        property["defend"] = 10;
        property["health"] = 100;
    default:
        property["attack"] = 10;
        property["defend"] = 10;
        property["health"] = 100;
    }
}

void MagicEnemy::paint(QPainter *painter)
{
    static int cnt = 120;
    painter->drawPixmap(x, y, cnt-- > 60 ? *pix[0] : *pix[1]);
    if (cnt <= 0) cnt = 120;
}

bool MagicEnemy::move(MagicMap *map)
{
    return runAction(map, false);
}
