#ifndef MAGICINVENTORY_H
#define MAGICINVENTORY_H

#include "magicdisplayobject.h"
#include "../magicmap.h"

class MagicInventory : public MagicDisplayObject
{

public:
    QPixmap *pix;
    MagicInventory(int, int, int, MagicMap *);
    ~MagicInventory();
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICINVENTORY_H
