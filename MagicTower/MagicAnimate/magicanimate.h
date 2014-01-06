#ifndef MAGICANIMATE_H
#define MAGICANIMATE_H

class MagicMap;

#include <QMutex>
#include <QPainter>

class MagicAnimate : public QMutex
{
    MagicMap *parent;
public:
    MagicAnimate(MagicMap *parent);
    virtual bool paint(QPainter *) = 0; // false -> please destroy me.
};

#endif // MAGICANIMATE_H
