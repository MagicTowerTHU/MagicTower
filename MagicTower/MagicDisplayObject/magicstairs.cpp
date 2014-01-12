#include "magicstairs.h"
#include "../magicmap.h"

MagicStairs::MagicStairs(int x, int y, int level, MagicMap *parent, int direction)
    : MagicFloor(x, y, level, parent)
{
    property["label"] = "stairs";
    appendClass("stairs");
    this->direction = direction;
    if(direction == 1)
        pix = new QPixmap(":/images/upstairs");
    else
        pix = new QPixmap(":/images/downstairs");
}

bool MagicStairs::move(MagicMap *map)
{
    switch(direction)
    {
    case 1:
        map->Tom()->setProperty("level", map->Tom()->property["level"] + 1);
        break;
    default:
        map->Tom()->setProperty("level", map->Tom()->property["level"] - 1);
        break;
    }
    return runAction(map, false);
}
