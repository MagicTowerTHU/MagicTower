#include "magicmap.h"
#include "MagicAnimate/magicanimate.h"
#include "MagicAnimate/magicmove.h"

#include <QPoint>
#include <QMutex>
#include <QTimer>
#include <QPointer>

MagicMap::MagicMap()
{
    animateTimer = new QTimer();
    //property["Tom"] = (long)(void *)
    mTom = new MagicTom();
    displayList.push_front(mTom);
    property["level"] = 1;
    //animateState = -1;

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
        (*mTom)["position_x"] = 0;
        (*mTom)["position_y"] = 0;
    }
}

void MagicMap::paint(QPainter *painter)
{
    animateListLock.lock();
    for (QList<MagicAnimate *>::iterator i = animateList.begin(); i != animateList.end(); i++)
        if ((*i)->paint(painter) == false)
        {
            (*i)->wakeAll();
            i = animateList.erase(i);
            if (animateList.empty())
            {
                animateLock.unlock();
                break;
            }
        }

    if (!animateList.empty())
    {
        animateLock.lock();
    }
    animateListLock.unlock();

    for (auto i = displayList.begin(); i != displayList.end(); i++)
        (*i)->paint(painter);
}

void MagicMap::appendAnimate(MagicAnimate *animate, bool block)
{
    animateListLock.lock();
    animateList.append(animate);
    if (block)
    {
        animate->wait(&animateListLock);
    }
    animateListLock.unlock();
}

void MagicMap::keyPressEvent(QKeyEvent *e)
{
    if (animateLock.tryLock())
    {
        animateLock.unlock();
        MagicMove *p;
        switch(e->key())
        {
        case Qt::Key_Down:
            if(mTom->setStep(0))
                appendAnimate(new MagicMove(this, 0, 1, mTom));
            break;
        case Qt::Key_Left:
            if(mTom->setStep(1))
                appendAnimate(new MagicMove(this, 1, 1, mTom));
            break;
        case Qt::Key_Up:
            if(mTom->setStep(2))
                appendAnimate(new MagicMove(this, 2, 1, mTom));
            break;
        case Qt::Key_Right:
            if(mTom->setStep(3))
                appendAnimate(new MagicMove(this, 3, 1, mTom));
            break;
        default:
            break;
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

QList<MagicObject *> MagicMap::findDisplayObject(QString objectLabel, QString objectId, QString objectClass)
{
    QList<MagicObject *> objects;
    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((objectLabel == "" || ((**i)["label"] == MagicVarient(objectLabel)).isTrue()) &&
                (objectId == "" || ((**i)["id"] == MagicVarient(objectId)).isTrue()) &&
                (objectClass == "" || ((**i)["class"] == MagicVarient(objectClass)).isTrue()))
            objects.append(*i);
    return objects;
}
