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

    MagicTom();
    virtual void paint(QPainter *painter);
    void change_pic(int, int);
    bool setStep(int);
    virtual bool move(MagicMap *);
    void show();
};

#endif // MAGICTOM_H
