#include "magicwall.h"

MagicWall::MagicWall(int x, int y)
{
    property["label"] = "wall";
    pix = new QPixmap(":/images/wall");
    this->x = 32 * x, this->y = 32 * y;
    property["position_x"] = x;
    property["position_y"] = y;
}

void MagicWall::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicWall::move(MagicMap *map)
{
    runAction(map);
    return false;
}
