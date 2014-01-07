#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

#include <QSound>

class MagicTom : public MagicDisplayObject
{
public:
    static QPixmap *Pix[4][3];
    QPixmap *pix;
    int animateState;

    QSound *mSound;
    QSound *mBeep;

    MagicTom();
    virtual void paint(QPainter *painter);
    virtual bool move();
    void change_pic(int, int);
    void moveTo(int, int);
    bool setStep(int);
    int direction();
};

#endif // MAGICTOM_H
