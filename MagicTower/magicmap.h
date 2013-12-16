#ifndef MAGICMAP_H
#define MAGICMAP_H

#include "magicfloor.h"
#include "magictom.h"
#include "magicdisplayobject.h"

#include <QMutex>
#include <QTimer>
#include <QFile>
#include <QKeyEvent>
#include <QList>

class MagicMap : public MagicDisplayObject
{
    MagicTom *mTom;
    QMutex *animateLock;
    QTimer *animateTimer;

    MagicFloor *floor[121];

    QList<MagicDisplayObject *> displayList;
    int animateState;

public:
    MagicMap();

    void loadMap(QFile * = NULL);
    virtual void paint(QPainter *);
    void keyPressEvent(QKeyEvent *);
};

#endif // MAGICMAP_H
