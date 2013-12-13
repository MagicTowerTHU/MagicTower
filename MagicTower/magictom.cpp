#include "magictom.h"

#include <QDir>
#include <QCoreApplication>

MagicTom::MagicTom()
{
    //pix = new QPixmap("../MagicTower/assets/images/1.PNG");
    pix = new QPixmap(":/images/1.png");
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
