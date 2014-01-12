#include "magicopen.h"
#include "../MagicDisplayObject/magicdoor.h"

MagicOpen::MagicOpen(MagicMap *map, MagicDoor *target)
    : MagicAnimate(map, 16)
{
    this->direction = direction;
    this->target = target;
    target->setProperty("enabled", 0);
}

bool MagicOpen::paint(QPainter *painter) // false -> please destroy me.
{
    if (duration > 0)
    {
        painter->drawPixmap(QPoint(target->x, target->y), *target->pix,
                            QRect(QPoint(16 - duration, 0), QPoint(16, 32)));
        painter->drawPixmap(QPoint(target->x + 32 - duration, target->y), *target->pix,
                            QRect(QPoint(16, 0), QPoint(16 + duration, 32)));
        duration--;
        return true;
    }
    else
        return false;
}
