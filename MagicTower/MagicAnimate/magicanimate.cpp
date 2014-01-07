#include "magicanimate.h"

MagicAnimate::MagicAnimate(MagicMap *parent)
{
    this->parent = parent;
}

MagicAnimate::MagicAnimate(MagicMap *parent, int duration)
{
    this->parent = parent;
    this->duration = duration;
}
