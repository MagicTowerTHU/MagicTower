#ifndef MAGICMAP_H
#define MAGICMAP_H

#include "magicfloor.h"
#include "magictom.h"
#include "magicdisplayobject.h"
#include "magicbacksound.h"

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
    MagicBackSound *mBackSound;

    MagicFloor *floor[121];

    QList<MagicDisplayObject *> displayList;
    QList<MagicObject *> objectList;
    int animateState;

public:
    MagicMap();

    void loadMap(QFile * = NULL);
    virtual void paint(QPainter *);
    void keyPressEvent(QKeyEvent *);
    QList<MagicObject *> findObject(QString, QString, QString);
    QList<MagicDisplayObject *> findDisplayObject(QString, QString, QString);
};

#endif // MAGICMAP_H
