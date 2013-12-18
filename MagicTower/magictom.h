#ifndef MAGICTOM_H
#define MAGICTOM_H

#include "magicdisplayobject.h"

#include <QSound>

class MagicTom : public MagicDisplayObject
{
public:
    QPixmap *pix,
    *pix_right, *pix_right_move[2],
    *pix_left, *pix_left_move[2],
    *pix_face, *pix_face_move[2],
    *pix_back, *pix_back_move[2];
    int animateState;
    int x, y;
    int dx, dy;

    QSound *mSound;
    QSound *mBeep;

    MagicTom();
    virtual void paint(QPainter *painter);
    void moveTo(int, int);
    bool setStep(int, int);
    int direction();
    void move();
    void show();
};

#endif // MAGICTOM_H
