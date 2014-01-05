#ifndef MAGICDISPLAYOBJECT_H
#define MAGICDISPLAYOBJECT_H

#include "magicobject.h"

#include <QPainter>

class MagicExpression;

class MagicDisplayObject : public MagicObject
{
    MagicExpression *action;

public:
    MagicDisplayObject();
    virtual void paint(QPainter *) = 0;
    virtual bool move();
    void setAction(MagicExpression *);
};

#endif // MAGICDISPLAYOBJECT_H
