#include "magictom.h"

MagicTom::MagicTom()
{
    pix = new QPixmap("../assets/1.PNG");
    x = y = 0;
}

void MagicTom::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

void MagicTom::move(double dx, double dy)
{
    x += dx, y += dy;
}
