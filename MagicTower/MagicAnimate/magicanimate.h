#ifndef MAGICANIMATE_H
#define MAGICANIMATE_H

class MagicMap;

#include <QWaitCondition>
#include <QMutex>
#include <QPainter>

class MagicAnimate : public QWaitCondition, public QMutex
{
    MagicMap *parent;
public:
    int duration;
    MagicAnimate(MagicMap *);
    MagicAnimate(MagicMap *, int);
    virtual bool paint(QPainter *) = 0; // false -> please destroy me.
};

#endif // MAGICANIMATE_H
