#ifndef MAGICMEDICINE_H
#define MAGICMEDICINE_H

#include "magicdisplayobject.h"

class MagicMedicine : public MagicDisplayObject
{
    QPixmap *pix;

public:
    MagicMedicine(int, int, int, QString);
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICMEDICINE_H
