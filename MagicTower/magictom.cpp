#include "magictom.h"

#include <QBitmap>

MagicTom::MagicTom()
{
    pix = new QPixmap(":/images/Tom");
    x = y = 0;
    mSound = new QSound(":/sounds/step");
    mBeep = new QSound(":/sounds/beep");
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
    if (x + dx > 320 || y + dy > 320 || x + dx < 0 || y + dy < 0)
    {
        mBeep->play();
        this->dx = this->dy = 0;
    }
    else
    {
        this->dx = dx, this->dy = dy;
        mSound->play();
    }
}

void MagicTom::move()
{
    x += dx, y += dy;
}
