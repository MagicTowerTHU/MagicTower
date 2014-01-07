#include "magicmove.h"
#include "../MagicDisplayObject/magictom.h"

MagicMove::MagicMove(MagicMap *parent, int direction, int distance, MagicDisplayObject *target)
    : MagicAnimate(parent)
{
    this->direction = direction;
    this->distance = distance;
    this->target = target;
    this->duration = distance * 8;
    this->step = this->distance * 32 / this->duration;
}

MagicMove::MagicMove(MagicMap *parent, int direction, int distance, MagicDisplayObject *target, int duration)
    : MagicAnimate(parent, duration)
{
    this->direction = direction;
    this->distance = distance;
    this->target = target;
    this->step = this->distance * 32 / this->duration;
}

bool MagicMove::paint(QPainter *)  // false -> please destroy me.
{
    int dx[4]={0, -step, 0, step}, dy[4]={step, 0, -step, 0};
    if (duration > 0)
    {
        MagicTom *tom = dynamic_cast<MagicTom *>(target);
        if(tom) tom->change_pic();
        duration--;
    }
    else
    {
    }
}
