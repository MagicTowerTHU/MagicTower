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
    if (!runAction(map))
        return false;
    if (map->Tom()->inventory.size() < 24)
    {
        int y = map->Tom()->inventory.size() / 12 + 12;
        int x = map->Tom()->inventory.size() % 12;
        map->Tom()->inventory.push_back(this);
        property["position_x"] = x;
        property["position_y"] = y;
        this->x = x * 32, this->y = y * 32;
    }
    return true;
}
