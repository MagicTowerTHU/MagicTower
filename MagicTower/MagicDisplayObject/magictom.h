#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

#include <QSound>

class MagicTom : public MagicDisplayObject
{
    QPixmap *Pix[4][3];
    QPixmap *pix;

public:

    QSound *mSound;
    QSound *mBeep;

    QList<MagicDisplayObject *> inventory;

    MagicTom();
    virtual void paint(QPainter *painter);
    void changePic(int, int);
    bool setStep(int);
    virtual bool move(MagicMap *);
    void show();
    bool haveInventory(QString);
    bool consumeInventory(QString);
    bool consumeInventory(QString, int);
};

#endif // MAGICTOM_H
