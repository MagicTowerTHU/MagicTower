#ifndef MAGICANY_H
#define MAGICANY_H

#include "magicdisplayobject.h"

class MagicAny : public MagicDisplayObject
{
    QPixmap *pix;

public:
    MagicAny(int, int ,int, MagicMap *);
    ~MagicAny();
    virtual void setProperty(QString, MagicVarient, bool = true);
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICANY_H
