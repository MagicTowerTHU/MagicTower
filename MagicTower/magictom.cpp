#include "magictom.h"

#include <QBitmap>

MagicTom::MagicTom()
{
    pix = new QPixmap(":/images/Tom");
    x = y = 0;
    mSound = new QSound(":/sounds/step");
}

void MagicTom::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

void MagicTom::moveTo(int tx, int ty)
{
    x = tx, y = ty;
}

void MagicTom::setStep(int dx, int dy)
{
    this->dx = dx, this->dy = dy;
    mSound->play();
}

void MagicTom::move()
{
    x += dx, y += dy;
}
