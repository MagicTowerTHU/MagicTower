#include "magicmap.h"
#include "magictom.h"
#include "magicfloor.h"

#include <QPoint>
#include <QMutex>
#include <QTimer>
#include <QPointer>

MagicMap::MagicMap()
{
    animateLock = new QMutex();
    animateTimer = new QTimer();
    property["Tom"] = (int)(void *)(mTom = new MagicTom());
    displayList.push_front(mTom);
    property["level"] = 1;
    animateState = -1;

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            displayList.push_front(floor[11 * i + j] = new MagicFloor(32 * i, 32 * j));
}

void MagicMap::loadMap(QFile *file)
{
    if (!file)
    {
        QPoint &_p = mTom->property["position"].toPoint();
        _p.setX(0), _p.setY(0);
    }
}

void MagicMap::paint(QPainter *painter)
{
    for (QList<MagicDisplayObject *>::iterator i = displayList.begin(); i != displayList.end(); i++)
        (*i)->paint(painter);

    if (animateState > 0)
        mTom->move(), animateState--;
    else if (animateState == 0)
    {
        animateState = -1;
        animateLock->unlock();
    }
}

void MagicMap::keyPressEvent(QKeyEvent *e)
{
    if (animateLock->tryLock())
    {
        animateState = 8;
        switch(e->key())
        {
        case Qt::Key_Left:
            mTom->setStep(-4, 0);
            break;
        case Qt::Key_Up:
            mTom->setStep(0, -4);
            break;
        case Qt::Key_Right:
            mTom->setStep(4, 0);
            break;
        case Qt::Key_Down:
            mTom->setStep(0, 4);
            break;
        default:
            animateState = 0;
        }
    }
}
