#ifndef MAGICDISPLAYOBJECT_H
#define MAGICDISPLAYOBJECT_H

#include "magicobject.h"

#include <QPainter>

class MagicDisplayObject : public MagicObject
{
public:
    MagicDisplayObject();
    virtual void paint(QPainter *) = 0;
};

#endif // MAGICDISPLAYOBJECT_H
