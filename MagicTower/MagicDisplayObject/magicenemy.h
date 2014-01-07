#ifndef MAGICENEMY_H
#define MAGICENEMY_H

#include "magicdisplayobject.h"

class MagicEnemy : public MagicDisplayObject
{
    QPixmap *pix[2];

public:
    MagicEnemy(int, int, QString);
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICENEMY_H
