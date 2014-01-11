#include "magicwit.h"
#include "../magicmap.h"

MagicWit::MagicWit(int x, int y, int level)
    : MagicInventory(x, y, level)
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
