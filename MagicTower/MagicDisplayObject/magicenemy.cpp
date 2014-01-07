#include "magicenemy.h"

#include <QPainter>

MagicEnemy::MagicEnemy(int x, int y, QString label)
{
    property["label"] = label;
    pix[0] = new QPixmap(":/images/enemy1.0");
    pix[1] = new QPixmap(":/images/enemy1.1");
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
    runAction(map);
    return false;
}
