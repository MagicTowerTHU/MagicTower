#ifndef MAGICWISDOM_H
#define MAGICWISDOM_H

#include "magicanimate.h"
#include "../magicmap.h"

class MagicWisdom : public MagicAnimate
{
    QPixmap *black, *wall;

public:
    MagicWisdom(MagicMap *);
    ~MagicWisdom();
    virtual bool paint(QPainter *);
};

#endif // MAGICWISDOM_H
