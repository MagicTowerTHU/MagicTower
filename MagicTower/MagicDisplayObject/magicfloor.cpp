#include "magicfloor.h"

MagicFloor::MagicFloor()
{
    property["label"] = "floor";
    pix = new QPixmap(":/images/floor");
}

MagicFloor::MagicFloor(int x, int y)
{
    pix = new QPixmap(":/images/floor");
    this->x = x, this->y = y;
}

void MagicFloor::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicFloor::move(MagicMap *map)
{
    if (!runAction(map))
        return false;
    return true;
}
