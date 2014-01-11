#include "magicanimate.h"

MagicAnimate::MagicAnimate(MagicMap *parent)
{
    this->parent = parent;
    wantDelete = false;
}

MagicAnimate::MagicAnimate(MagicMap *parent, int duration)
{
    this->parent = parent;
    this->duration = duration;
    wantDelete = false;
}
