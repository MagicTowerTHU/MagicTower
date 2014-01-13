#ifndef MAGICPOPUP_H
#define MAGICPOPUP_H

#include "magicanimate.h"

class MagicPopup : public MagicAnimate
{
    int cnt = 0;
    QString content;
    static QRect screen;
    QPixmap background;

public:
    MagicPopup(MagicMap *, QString);
    virtual bool paint(QPainter *);
};

#endif // MAGICPOPUP_H
