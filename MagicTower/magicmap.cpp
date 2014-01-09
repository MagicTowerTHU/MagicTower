#include "magicmap.h"
#include "MagicAnimate/magicanimate.h"
#include "MagicAnimate/magicmove.h"
#include "MagicDisplayObject/magicenemy.h"
#include "MagicDisplayObject/magicstairs.h"
#include "MagicDisplayObject/magicwall.h"
#include "MagicDisplayObject/magicdoor.h"
#include "MagicDisplayObject/magickey.h"

#include <QPoint>
#include <QMutex>
#include <QTimer>
#include <QPointer>
#include <QSound>

#define yellow 0
#define blue 1
#define red 2
#define silver 3

MagicMap::MagicMap()
{
    animateTimer = new QTimer();
    //property["Tom"] = (long)(void *)
    mTom = new MagicTom();
    displayList.push_front(mTom);
    property["level"] = 1;

    animateFlag = false;

    displayList.push_front(new MagicEnemy(3, 4, "enemy1"));

    displayList.push_front(new MagicStairs(0, 10, 1));
    displayList.push_front(new MagicStairs(10, 0, -1));

    displayList.push_front(new MagicWall(0, 1));
    displayList.push_front(new MagicWall(0, 2));
    displayList.push_front(new MagicWall(1, 2));
    displayList.push_front(new MagicWall(0, 1));
    displayList.push_front(new MagicWall(2, 0));
    displayList.push_front(new MagicWall(3, 0));
    displayList.push_front(new MagicWall(4, 0));
    displayList.push_front(new MagicWall(5, 0));
    displayList.push_front(new MagicDoor(2, 2, yellow));
    displayList.push_front(new MagicWall(3, 2));
    displayList.push_front(new MagicDoor(4, 2, yellow));
    displayList.push_front(new MagicWall(5, 2));
    displayList.push_front(new MagicDoor(6, 2, red));
    displayList.push_front(new MagicWall(7, 2));
    displayList.push_front(new MagicWall(7, 1));
    displayList.push_front(new MagicDoor(8, 1, blue));
    displayList.push_front(new MagicWall(9, 1));
    displayList.push_front(new MagicDoor(10, 1, silver));

    displayList.push_front(new MagicKey(2, 1, yellow));
    displayList.push_front(new MagicKey(3, 1, yellow));
    displayList.push_front(new MagicKey(4, 1, red));
    displayList.push_front(new MagicKey(5, 1, blue));


    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            displayList.push_front(floor[11 * i + j] = new MagicFloor(i, j));

    for (int i = 12; i < 14; i++)
        for (int j = 0; j < 12; j++)
            displayList.push_front(inventory[12 * i + j] = new MagicFloor(j, i));

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
            (*i)->lock();
            (*i)->wakeAll();
            (*i)->unlock();
            i = animateList.erase(i);
            if (animateList.empty())
            {
                animateFlag = false;
                break;
            }
        }
    animateListLock.unlock();

    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((**i)["enabled"].isTrue())
            (*i)->paint(painter);

    for (auto i = mTom->inventory.begin(); i != mTom->inventory.end(); i++)
        (*i)->paint(painter);
}

void MagicMap::appendAnimate(MagicAnimate *animate, bool block)
{
    if (block)
        animate->lock();
    animateListLock.lock();
    animateList.append(animate);
    animateFlag = true;
    animateListLock.unlock();
    if (block)
    {
        animate->wait(animate);
        animate->unlock();
    }
}

void MagicMap::keyPressEvent(QKeyEvent *e)
{
    if (!animateFlag)
    {
        MagicMove *p;
        switch (e->key())
        {
        case Qt::Key_Down:
            mTom->changePic(0,0);
            if (move(0, 1))
                appendAnimate(new MagicMove(this, 0, 1, mTom), false);
            break;
        case Qt::Key_Left:
            mTom->changePic(1,0);
            if (move(1, 1))
                appendAnimate(new MagicMove(this, 1, 1, mTom), false);
            break;
        case Qt::Key_Up:
            mTom->changePic(2,0);
            if (move(2, 1))
                appendAnimate(new MagicMove(this, 2, 1, mTom), false);
            break;
        case Qt::Key_Right:
            mTom->changePic(3,0);
            if (move(3, 1))
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

bool MagicMap::move(int direction, int distance)
{
    int target_x = (*mTom)["position_x"].getInt() + dx[direction] * distance,
        target_y = (*mTom)["position_y"].getInt() + dy[direction] * distance;

    if (target_x < 0 || target_x > 10 || target_y < 0 || target_y > 10)
    {
        mTom->mBeep->play();
        return false;
    }

    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((**i)["position_x"].getInt() == target_x && (**i)["position_y"].getInt() == target_y)
            if ((**i)["enabled"].isTrue() && !(*i)->move(this))
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

void MagicMap::setProperty(QString propertyName, MagicVarient propertyValue)
{
    if (propertyName == "sound")
    {
        (new QSound(propertyValue.getString()))->play();
        return;
    }
    MagicObject::setProperty(propertyName, propertyValue);
}

bool MagicMap::eraseMapObject(QString label, int x, int y)
{
    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ( ((**i)["label"] == MagicVarient(label)).isTrue() &&
             (**i)["position_x"].getInt() == x &&
             (**i)["position_y"].getInt() == y)
        {
            i = displayList.erase(i);
            return true;
        }
    return false;
}

MagicTom * MagicMap::Tom()
{
    return this->mTom;
}
