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
    MagicDisplayObject(int, int, int);
    ~MagicDisplayObject();
    virtual void paint(QPainter *) = 0;
    virtual bool move(MagicMap *) = 0;
    virtual void setProperty(QString, MagicVarient);

    void setAction(MagicExpression *);
    bool runAction(MagicMap *, bool);
};

#endif // MAGICDISPLAYOBJECT_H
