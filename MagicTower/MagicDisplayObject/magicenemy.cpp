#include "magicenemy.h"

#include <QPainter>

MagicEnemy::MagicEnemy(int x, int y)
{
    property["label"] = "enemy";
    pix[0] = new QPixmap(":/images/guai_1");
    pix[1] = new QPixmap(":/images/guai_2");
    this->x = 32 * x, this->y = 32 * y;
    property["position_x"] = x;
    property["position_y"] = y;
}

void MagicEnemy::paint(QPainter *painter)
{
    static int cnt = 12;
    painter->drawPixmap(x, y, cnt-- > 6 ? *pix[0] : *pix[1]);
    if (cnt <= 0) cnt = 12;
}

bool MagicEnemy::move(MagicMap *map)
{
    if (!runAction(map))
        return false;
    return true;
}
