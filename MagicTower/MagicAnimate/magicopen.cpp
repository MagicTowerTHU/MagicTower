#include "magicopen.h"

MagicOpen::MagicOpen(MagicMap *map, int direction, MagicDoor *target, int duration)
    : MagicAnimate(map, duration)
{
    this->direction = direction;
    this->target = target;
}

bool MagicOpen::paint(QPainter *) // false -> please destroy me.
{
    if (duration > 0)
    {
        target->pix->scroll(-1, 0, 0, 0, duration, 32);
        duration--;
        return true;
    }
    else
        return false;
}
