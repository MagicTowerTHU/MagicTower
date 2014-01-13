#include "magicwall.h"
#include "../magicmap.h"

MagicWall::MagicWall(int x, int y, int level, MagicMap *parent)
    : MagicDisplayObject(x, y, level, parent)
{
    property["label"] = "wall";
    appendClass("wall");
    pix = new QPixmap(":/images/wall");
}

MagicWall::~MagicWall()
{
    delete pix;
}

void MagicWall::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicWall::move(MagicMap *map)
{
    if (!runAction(map, false))
    {
        parent->appendSound(":/sounds/beep");
        return false;
    }
    return true;
}
