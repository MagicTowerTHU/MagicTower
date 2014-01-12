#ifndef MAGICALTWALL_H
#define MAGICALTWALL_H
#include "magicwall.h"

class MagicAltWall : public MagicWall
{
    int cnt = 20;
public:
    MagicAltWall(int, int, int, MagicMap *, QString);
    virtual void paint(QPainter *);
};

#endif // MAGICALTWALL_H
