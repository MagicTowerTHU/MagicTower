#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

#include <QSound>

class MagicTom : public MagicDisplayObject
{
    QPixmap *Pix[4][3];
    QPixmap *pix;

public:
    QList<MagicDisplayObject *> inventory;

    MagicTom(int, int, int);
    virtual void paint(QPainter *painter);
    void changePic(int, int);
    bool setStep(int);
    virtual bool move(MagicMap *);
    bool haveInventory(QString);
    bool consumeInventory(QString);
    bool consumeInventory(QString, int);
};

#endif // MAGICTOM_H
