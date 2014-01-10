#include "magicfloor.h"

MagicFloor::MagicFloor(int x, int y)
{
    property["label"] = "floor";
    pix = new QPixmap(":/images/floor");
    this->x = 32 * x, this->y = 32 * y;
    property["position_x"] = x;
    property["position_y"] = y;
}

void MagicFloor::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicFloor::move(MagicMap *map)
{
    return runAction(map, true);
}
