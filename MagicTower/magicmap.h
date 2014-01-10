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

class MagicMap : public MagicObject
{
    MagicTom *mTom;
    MagicBackSound *mBackSound;

    MagicFloor *floor[121];
    MagicFloor *inventory[24];

    QList<MagicDisplayObject *> displayList;

    QList<MagicAnimate *> animateList;
    bool animateFlag;
    QTimer *animateTimer;
    QMutex animateListLock;
    QWaitCondition appendingAnimate;

    bool move(int, int); // direction

public:
    MagicMap();

    void loadMap(QFile * = NULL);
    void paint(QPainter *);
    void keyPressEvent(QKeyEvent *);

    void appendAnimate(MagicAnimate *, bool = true);

    QList<MagicObject *> findDisplayObject(QString, QString, QList<QString>);

    virtual void setProperty(QString, MagicVarient);
    bool eraseMapObject(QString, int, int);

    MagicTom *Tom();
};

#endif // MAGICMAP_H
