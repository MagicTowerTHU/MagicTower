#include "magicinventory.h"

MagicInventory::MagicInventory(int x, int y, int level)
    : MagicDisplayObject(x, y, level)
{

}

MagicInventory::~MagicInventory()
{
    delete pix;
}

void MagicInventory::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicInventory::move(MagicMap *map)
{
    if (map->Tom()->inventory.size() < 24)
    {
        property["enabled"] = 0;
        property["picked"] = 1;
        map->Tom()->inventory.push_back(this);
    }
    return runAction(map, true);
}
