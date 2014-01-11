#include "magicfloor.h"

MagicFloor::MagicFloor(int x, int y, int level)
    : MagicDisplayObject(x, y, level)
{
    property["label"] = "floor";
    appendClass("floor");
    pix = new QPixmap(":/images/floor");
}

MagicFloor::~MagicFloor()
{
    delete pix;
}

void MagicFloor::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicFloor::move(MagicMap *map)
{
    return runAction(map, true);
}
