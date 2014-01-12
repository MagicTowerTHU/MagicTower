#ifndef MAGICENEMY_H
#define MAGICENEMY_H

#include "magicdisplayobject.h"

class MagicEnemy : public MagicDisplayObject
{
    int cnt = 0;

public:
    QPixmap *pix[2];
    MagicEnemy(int, int, int, MagicMap *, QString);
    ~MagicEnemy();
    int damage(MagicMap *);
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICENEMY_H
