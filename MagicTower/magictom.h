#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

#include <QSound>

class MagicTom : public MagicDisplayObject
{
    QPixmap *pix;
    int x, y;
    int dx, dy;

    QSound *mSound;
    QSound *mBeep;

public:
    MagicTom();
    virtual void paint(QPainter *painter);
    void moveTo(int, int);
    void setStep(int, int);
    void move();
};

#endif // MAGICTOM_H
