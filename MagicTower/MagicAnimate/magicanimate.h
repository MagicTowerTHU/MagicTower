#ifndef MAGICANIMATE_H
#define MAGICANIMATE_H

class MagicMap;

#include <QWaitCondition>
#include <QMutex>
#include <QPainter>

#include "../MagicDisplayObject/magicdisplayobject.h"

class MagicAnimate : public QWaitCondition, public QMutex
{
protected:
    MagicMap *parent;
public:
    bool wantDelete;
    int duration;
    MagicAnimate(MagicMap *);
    MagicAnimate(MagicMap *, int);
    virtual bool paint(QPainter *) = 0; // false -> please destroy me.
};

#endif // MAGICANIMATE_H
