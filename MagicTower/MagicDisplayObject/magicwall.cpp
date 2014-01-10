#include "magicwall.h"

MagicWall::MagicWall(int x, int y, int level)
    : MagicDisplayObject(x, y, level)
{
    property["label"] = "wall";
    pix = new QPixmap(":/images/wall");
}

void MagicWall::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicWall::move(MagicMap *map)
{
    return runAction(map, false);
}
