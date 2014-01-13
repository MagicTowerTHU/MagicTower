#include "magicmove.h"
#include "../MagicDisplayObject/magictom.h"

MagicMove::MagicMove(MagicMap *parent, int direction, int distance, MagicDisplayObject *target, int duration)
    : MagicAnimate(parent)
{
    this->direction = direction;
    this->distance = distance;
    this->target = target;
    if (duration < 0)
        this->duration = distance * 8;
    else
        this->duration = duration;
    this->step = this->distance * 32 / this->duration;
}

bool MagicMove::paint(QPainter *)  // false -> please destroy me.
{
    int dx[4]={0, -step, 0, step}, dy[4]={step, 0, -step, 0};
    if (duration > 0)
    {
        MagicTom *tom = dynamic_cast<MagicTom *>(target);
        if(tom) tom->changePic(direction, duration);
        target->x += dx[direction];
        target->y += dy[direction];
        duration--;
        return true;
    }
    else
    {
        MagicTom *tom = dynamic_cast<MagicTom *>(target);
        if(tom) tom->changePic(direction, duration);
        (*target)["position_x"] += dx[direction] / step;
        (*target)["position_y"] += dy[direction] / step;
        return false;
    }
}
