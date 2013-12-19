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
    //property["Tom"] = (long)(void *)
    mTom = new MagicTom();
    displayList.push_front(mTom);
    property["level"] = 1;
    animateState = -1;

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            displayList.push_front(floor[11 * i + j] = new MagicFloor(32 * i, 32 * j));

    mBackSound = new MagicBackSound();
    mBackSound->play(QSound::Infinite);
}

void MagicMap::loadMap(QFile *file)
{
    if (!file)
    {
        QPoint _p;
        _p.setX(0), _p.setY(0);
        mTom->property["position"] = _p;
    }
}

void MagicMap::paint(QPainter *painter)
{
    for (QList<MagicDisplayObject *>::iterator i = displayList.begin(); i != displayList.end(); i++)
        (*i)->paint(painter);

    if (animateState > 0)
    {
        mTom->move();
        mTom->animateState = animateState;
        mTom->show();
        animateState --;
        //if(animateState == 1) animateLock->unlock();
    }
    else if (animateState == 0)
    {
        animateState = -1;
        mTom->animateState = animateState;
        mTom->show();
        //if(animateState == 1)
        animateLock->unlock();
    }
}

void MagicMap::keyPressEvent(QKeyEvent *e)
{
    if (animateLock->tryLock())
    {
        switch(e->key())
        {
        case Qt::Key_Left:
            animateState =  (mTom->setStep(-4, 0)) ? 8 : 0;
            break;
        case Qt::Key_Up:
            animateState =  (mTom->setStep(0, -4)) ? 8 : 0;
            break;
        case Qt::Key_Right:
            animateState =  (mTom->setStep(4, 0)) ? 8 : 0;
            break;
        case Qt::Key_Down:
            animateState =  (mTom->setStep(0, 4)) ? 8 : 0;
            break;
        default:
            animateState = 0;
        }
        switch(e->key())
        {
        case Qt::Key_0: mBackSound->change(0); break;
        case Qt::Key_1: mBackSound->change(1); break;
        case Qt::Key_2: mBackSound->change(2); break;
        case Qt::Key_3: mBackSound->change(3); break;
        }
    }
}