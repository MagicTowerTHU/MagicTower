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

    MagicFloor *floor[121];
    MagicFloor *inventory[24];

    QTimer *animateTimer;
    QMutex animateListLock;
    QWaitCondition appendingAnimate;

    void destoryList();
    void initialize();

public:
    bool animateFlag;
    QList<MagicAnimate *> animateList;
    MagicBackSound *mBackSound;

    bool move(int, int); // direction

    MagicMap();
    QList<MagicDisplayObject *> displayList;

    bool loadMap(QFile * = NULL);
    bool saveRecord(QFile * = NULL);
    bool loadRecord(QFile * = NULL);
    void paint(QPainter *);
    void keyPressEvent(QKeyEvent *);

    void appendAnimate(MagicAnimate *, bool);
    void appendObject(MagicDisplayObject *);

    QList<MagicObject *> findDisplayObject(QString, QString, QList<QString>);
    const virtual MagicVarient& operator[](QString) const;

    virtual void setProperty(QString, MagicVarient);
    //bool eraseMapObject(QString, int, int);

    MagicTom *Tom();
};

#endif // MAGICMAP_H
