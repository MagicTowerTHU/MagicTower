#include "magicinventory.h"

MagicInventory::MagicInventory(int x, int y, int level, MagicMap *parent)
    : MagicDisplayObject(x, y, level, parent)
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
    //if (map->Tom()->inventory.size() < 33)
    {
        property["enabled"] = 0;
        setProperty("pick", 1);
    }
    return runAction(map, false);
}
