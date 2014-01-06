#ifndef MAGICMAP_H
#define MAGICMAP_H

#include "MagicDisplayObject/magicfloor.h"
#include "MagicDisplayObject/magictom.h"
#include "MagicDisplayObject/magicdisplayobject.h"
#include "magicbacksound.h"
#include "MagicAnimate/magicanimate.h"

#include <QMutex>
#include <QTimer>
#include <QFile>
#include <QKeyEvent>
#include <QList>
#include <QWaitCondition>

class MagicMap
{
    MagicTom *mTom;
    MagicBackSound *mBackSound;

    MagicFloor *floor[121];

    QList<MagicDisplayObject *> displayList;
    QList<MagicObject *> objectList;
    QMutex animateLock;
    QTimer *animateTimer;
    QList<MagicAnimate *> animateList;
    QMutex animateListLock;
    QWaitCondition appendingAnimate;

public:
    MagicMap();

    void loadMap(QFile * = NULL);
    virtual void paint(QPainter *);
    void keyPressEvent(QKeyEvent *);

    void appendAnimate(MagicAnimate *, bool = true);

    QList<MagicObject *> findObject(QString, QString, QString);
    QList<MagicDisplayObject *> findDisplayObject(QString, QString, QString);
};

#endif // MAGICMAP_H
