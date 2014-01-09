#include "magicenemy.h"

#include <QPainter>

MagicEnemy::MagicEnemy(int x, int y, QString name)
{
    property["label"] = "enemy_" + name;
    pix[0] = new QPixmap(":/images/enemy_" + name + ".0");
    pix[1] = new QPixmap(":/images/enemy_" + name + ".1");
    this->x = 32 * x, this->y = 32 * y;
    property["position_x"] = x;
    property["position_y"] = y;
}

void MagicEnemy::paint(QPainter *painter)
{
    static int cnt = 120;
    painter->drawPixmap(x, y, cnt-- > 60 ? *pix[0] : *pix[1]);
    if (cnt <= 0) cnt = 120;
}

bool MagicEnemy::move(MagicMap *map)
{
    runAction(map);
    return false;
}
