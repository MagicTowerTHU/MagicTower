#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

#include <QSound>

class MagicTom : public MagicDisplayObject
{
    QPixmap *Pix[4][3];
    QPixmap *pix;

public:
    int range;
    MagicTom(int, int, int, MagicMap *);
    QList<MagicDisplayObject *> inventory;

    virtual void paint(QPainter *painter);
    void changePic(int, int);
    virtual bool move(MagicMap *);
    virtual void setProperty(QString, MagicVarient);
    bool haveInventory(QString);
    bool consumeInventory(QString);
    bool consumeInventory(QString, int);
};

#endif // MAGICTOM_H
