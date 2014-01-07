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
        if ((**i)["enabled"].isTrue())
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
        switch (e->key())
        {
        case Qt::Key_Down:
            if (move(0))
                appendAnimate(new MagicMove(this, 0, 1, mTom), false);
            break;
        case Qt::Key_Left:
            if (move(1))
                appendAnimate(new MagicMove(this, 1, 1, mTom), false);
            break;
        case Qt::Key_Up:
            if (move(2))
                appendAnimate(new MagicMove(this, 2, 1, mTom), false);
            break;
        case Qt::Key_Right:
            if (move(3))
                appendAnimate(new MagicMove(this, 3, 1, mTom), false);
            break;
        default:
            break;
        }
        switch (e->key())
        {
        case Qt::Key_0: mBackSound->change(0); break;
        case Qt::Key_1: mBackSound->change(1); break;
        case Qt::Key_2: mBackSound->change(2); break;
        case Qt::Key_3: mBackSound->change(3); break;
        }
    }
}

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

bool MagicMap::move(int direction)
{
    int target_x = (*mTom)["position_x"].getInt() + dx[direction],
        target_y = (*mTom)["position_y"].getInt() + dy[direction];

    if (target_x < 0 || target_x > 10 || target_y < 0 || target_y > 10)
    {
        mTom->mBeep->play();
        return false;
    }

    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((**i)["position_x"].getInt() == target_x && (**i)["position_y"].getInt() == target_y)
            if (!(*i)->move(this))
            {
                mTom->mBeep->play();
                return false;
            }

    return true;
}

QList<MagicObject *> MagicMap::findDisplayObject(QString objectLabel, QString objectId, QString objectClass)
{
    QList<MagicObject *> objects;
    if (objectLabel == "global" || objectLabel == "map")
    {
        objects.append(this);
        return objects;
    }
    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((objectLabel == "" || ((**i)["label"] == MagicVarient(objectLabel)).isTrue()) &&
                (objectId == "" || ((**i)["id"] == MagicVarient(objectId)).isTrue()) &&
                (objectClass == "" || ((**i)["class"] == MagicVarient(objectClass)).isTrue()))
            objects.append(*i);
    return objects;
}
