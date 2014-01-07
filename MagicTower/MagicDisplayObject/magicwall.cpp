#include "magicwall.h"

MagicWall::MagicWall()
{
    property["label"] = "wall";
}

void MagicWall::paint(QPainter *painter)
{

}

bool MagicWall::move(MagicMap *map)
{
    runAction(map);
    return false;
}
