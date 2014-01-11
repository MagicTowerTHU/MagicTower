#include "magicwit.h"
#include "../magicmap.h"

MagicWit::MagicWit(int x, int y, int level, MagicMap *parent)
    : MagicInventory(x, y, level, parent)
{
    pix = new QPixmap(":/images/wit");
    property["label"] = "wit";
    appendClass("wit");
}

bool MagicWit::move(MagicMap *map)
{
    map->property["wisdomEnabled"] = 1;
    return MagicInventory::move(map);
}
