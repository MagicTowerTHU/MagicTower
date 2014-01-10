#include "magicinventory.h"

MagicInventory::MagicInventory(int x, int y)
{
    property["position_x"] = x;
    property["position_y"] = y;
    this->x = x * 32, this->y = y * 32;
}

void MagicInventory::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicInventory::move(MagicMap *map)
{
    if (map->Tom()->inventory.size() < 24)
    {
        map->eraseMapObject(property["label"].getString(), property["position_x"].getInt(), property["position_y"].getInt());
        map->Tom()->inventory.push_back(this);
    }
    return runAction(map, true);
}
