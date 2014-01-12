#ifndef MAGICLEVEL_H
#define MAGICLEVEL_H

#include "magicanimate.h"

#include <QRect>

class MagicLevel : public MagicAnimate
{
    int cnt = 0;
    int level;
    QString buffer;
    static QRect screen;

public:
    MagicLevel(MagicMap *, int);
    virtual bool paint(QPainter *);
};

#endif // MAGICLEVEL_H
