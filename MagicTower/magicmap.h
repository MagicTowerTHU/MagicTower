#ifndef MAGICMAP_H
#define MAGICMAP_H

#include "MagicDisplayObject/magicfloor.h"
#include "MagicDisplayObject/magictom.h"
#include "MagicDisplayObject/magicdisplayobject.h"
#include "magicbacksound.h"
#include "MagicAnimate/magicanimate.h"

#include <QMutex>
#include <QReadWriteLock>
#include <QTimer>
#include <QFile>
#include <QKeyEvent>
#include <QList>
#include <QWaitCondition>

class KeyThread;

class MagicMap : public MagicObject
{
    friend class Widget;

    MagicTom *mTom;

    MagicFloor *floor[121];
    MagicFloor *inventory[24];

    QTimer *animateTimer;

    void destoryList();
    void initialize();

    QStringList soundToPlay;
    QMutex soundListLock;

    QString mapPath;

public:
    int animateFlag = 0;
    QList<MagicAnimate *> animateList;
    QReadWriteLock animateListLock;

    MagicBackSound *mBackSound;

    bool move(int, int); // direction

    MagicMap();
    QList<MagicDisplayObject *> displayList;

    bool loadMap(QString = "");
    bool saveRecord(QFile * = NULL);
    bool loadRecord(QFile * = NULL);
    void paint(QPainter *);

    int eventFlag = 0;
    void keyPressEvent(QKeyEvent *);

    void appendPopup(QString, bool = false);
    void appendAnimate(MagicAnimate *, bool);
    void appendObject(MagicDisplayObject *);

    void appendSound(QString);

    QList<MagicObject *> findDisplayObject(QString, QString, QList<QString>);

    virtual void setProperty(QString, MagicVarient, bool = true);
    //bool eraseMapObject(QString, int, int);

    void setPath(QString);
    QString getResource(QString);

    MagicTom *Tom();
};

#endif // MAGICMAP_H
