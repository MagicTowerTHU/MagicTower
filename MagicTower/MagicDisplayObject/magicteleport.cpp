#include "magicteleport.h"

MagicTeleport::MagicTeleport(int x, int y, int level, MagicMap *parent)
    : MagicInventory(x, y, level, parent)
{
    property["label"] = "teleport";
    appendClass("teleport");
    pix = new QPixmap(":/images/teleport");
}

bool MagicTeleport::move(MagicMap *map)
{
    map->property["teleportEnabled"] = 1;
    return MagicInventory::move(map);
}
