#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

class MagicKey;

#include <QSound>
#include <QMap>

class MagicTom : public MagicDisplayObject
{
    QPixmap *Pix[4][3];
    QPixmap *pix;
    QList<MagicKey *> backupKey0;
    QList<MagicKey *> backupKey1;
    QList<MagicKey *> backupKey2;

public:
    MagicTom(int, int, int, MagicMap *);
    QList<MagicDisplayObject *> inventory;

    virtual void paint(QPainter *painter);
    void changePic(int, int);
    virtual bool move(MagicMap *);
    virtual void setProperty(QString, MagicVarient, bool = true);
    virtual MagicVarient &operator[](QString);
    virtual const MagicVarient &operator[](QString) const;
    bool haveInventory(QString);
    bool consumeInventory(QString);
    bool consumeInventory(QString, int);
};

#endif // MAGICTOM_H
