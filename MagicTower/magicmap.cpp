#include "magicmap.h"

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
        (*mTom)["position_x"] = 0;
        (*mTom)["position_y"] = 0;
    }
}

void MagicMap::paint(QPainter *painter)
{
    for (auto i = displayList.begin(); i != displayList.end(); i++)
        (*i)->paint(painter);
    for (QList<MagicAnimate *>::iterator i = animateList.begin(); i != animateList.end(); i++)
        if ((*i)->paint(painter) == false)
            i = animateList.erase(i);

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

QList<MagicObject *> MagicMap::findObject(QString objectLabel, QString objectId, QString objectClass)
{
    QList<MagicObject *> objects;
    for (auto i = objectList.begin(); i != objectList.end(); i++)
        if ((objectLabel == "" || ((**i)["label"] == objectLabel).isTrue()) &&
                (objectId == "" || ((**i)["id"] == objectId).isTrue()) &&
                (objectClass == "" || ((**i)["class"] == objectClass).isTrue()))
            objects.append(*i);
    return objects;
}

QList<MagicDisplayObject *> MagicMap::findDisplayObject(QString objectLabel, QString objectId, QString objectClass)
{
    QList<MagicDisplayObject *> objects;
    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((objectLabel == "" || ((**i)["label"] == MagicVarient(objectLabel)).isTrue()) &&
                (objectId == "" || ((**i)["id"] == MagicVarient(objectId)).isTrue()) &&
                (objectClass == "" || ((**i)["class"] == MagicVarient(objectClass)).isTrue()))
            objects.append(*i);
    return objects;
}
