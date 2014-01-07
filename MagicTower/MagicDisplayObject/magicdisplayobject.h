#ifndef MAGICDISPLAYOBJECT_H
#define MAGICDISPLAYOBJECT_H

#include "../magicobject.h"

class MagicMap;

#include <QPainter>

class MagicExpression;

class MagicDisplayObject : public MagicObject
{
    MagicExpression *action;

public:
    int x, y;
    MagicDisplayObject();
    virtual void paint(QPainter *) = 0;
    virtual bool move(MagicMap *) = 0;

    void setAction(MagicExpression *);
    int runAction(MagicMap *);
};

#endif // MAGICDISPLAYOBJECT_H
