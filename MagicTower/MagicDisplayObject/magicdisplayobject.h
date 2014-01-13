#ifndef MAGICDISPLAYOBJECT_H
#define MAGICDISPLAYOBJECT_H

#include "../magicobject.h"

class MagicMap;

#include <QPainter>
#include <QList>

class MagicExpression;

class MagicDisplayObject : public MagicObject
{
    QList<MagicExpression *>action;

protected:
    MagicMap *parent;
    virtual QString getLabel();

public:
    int x, y;
    MagicDisplayObject(int, int, int, MagicMap *);
    virtual ~MagicDisplayObject();
    virtual void paint(QPainter *) = 0;
    virtual bool move(MagicMap *) = 0;
    virtual void setProperty(QString, MagicVarient, bool = true);

    void setAction(MagicExpression *);
    bool runAction(MagicMap *, bool);
};

#endif // MAGICDISPLAYOBJECT_H
