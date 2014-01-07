#ifndef MAGICDISPLAYOBJECT_H
#define MAGICDISPLAYOBJECT_H

#include "../magicobject.h"

#include <QPainter>

class MagicExpression;

class MagicDisplayObject : public MagicObject
{
    MagicExpression *action;

public:
    int x, y;
    MagicDisplayObject();
    virtual void paint(QPainter *) = 0;
    virtual bool move();
    virtual void show() = 0;
    void setAction(MagicExpression *);
};

#endif // MAGICDISPLAYOBJECT_H
