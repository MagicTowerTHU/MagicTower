#ifndef MAGICMERCHANT_H
#define MAGICMERCHANT_H

#include "magicdisplayobject.h"
#include "../MagicAnimate/magicinputbox.h"

class MagicMerchant : public MagicDisplayObject
{
    int cnt = 0;
    QPixmap *pix[2];

public:
    MagicMerchant(int, int, int, QString, MagicMap *);
    ~MagicMerchant();
    virtual void paint(QPainter *);
    virtual bool move(MagicMap *);
};

#endif // MAGICMERCHANT_H
