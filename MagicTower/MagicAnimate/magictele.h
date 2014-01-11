#ifndef MAGICTELE_H
#define MAGICTELE_H

#include "magicanimate.h"

class MagicTele : public MagicAnimate
{
    QPixmap *floor, *wall, *chosen;
    QString content;
    int xChoose, yChoose;

public:
    MagicTele(MagicMap *, QString = "你想去哪层?");
    ~MagicTele();
    virtual bool paint(QPainter *);
    void input(int);
};

#endif // MAGICTELE_H
