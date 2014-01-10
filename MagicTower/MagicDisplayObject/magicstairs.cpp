#include "magicstairs.h"

MagicStairs::MagicStairs(int x, int y, int level, int direction)
    : MagicFloor(x, y, level)
{
    property["label"] = "stairs";
    this->direction = direction;
    if(direction == 1)
        pix = new QPixmap(":/images/upstairs");
    else
        pix = new QPixmap(":/images/downstairs");
}

bool MagicStairs::move(MagicMap *map)
{
    return runAction(map, true);
}
