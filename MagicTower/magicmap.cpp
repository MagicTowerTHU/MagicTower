#include "magicmap.h"
#include "MagicAnimate/magicanimate.h"
#include "MagicAnimate/magicmove.h"
#include "MagicDisplayObject/magicenemy.h"
#include "MagicDisplayObject/magicstairs.h"
#include "MagicDisplayObject/magicwall.h"
#include "MagicDisplayObject/magicdoor.h"
#include "MagicDisplayObject/magickey.h"
#include "MagicDisplayObject/magicweapon.h"
#include "MagicDisplayObject/magicarmour.h"

#include <QPoint>
#include <QPointer>
#include <QSound>
#include <QDebug>

#define yellow 0
#define blue 1
#define red 2
#define silver 3

MagicMap::MagicMap()
{
    animateTimer = new QTimer();

    mTom = new MagicTom(0, 0, 1);
    displayList.push_front(mTom);
    property["level"] = 1;

    animateFlag = false;

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
                displayList.push_front(floor[11 * i + j] = new MagicFloor(i, j, 1));

    for (int i = 12; i < 14; i++)
        for (int j = 0; j < 12; j++)
                displayList.push_front(inventory[12 * i + j] = new MagicFloor(j, i, 1));

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
        if ((**i)["enabled"].isTrue() &&
            (((**i)["level"] == mTom->property["level"]).isTrue() || (**i)["label"].getString() == "floor"))
            (*i)->paint(painter);

    int j = 0;
    for (auto i = mTom->inventory.begin(); i != mTom->inventory.end(); i++)
    {
        int x = j % 12;
        int y = j / 12 + 12;
        (**i)["position_x"] = x, (**i)["position_y"] = y;
        (*i)->x = x * 32, (*i)->y = y * 32;
        (*i)->paint(painter);
        j++;
    }
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

void MagicMap::appendObject(MagicDisplayObject *target)
{
    if (!target)
        throw "What are you doing?";
    displayList.push_back(target);
}

void MagicMap::keyPressEvent(QKeyEvent *e)
{
    if (!animateFlag)
    {
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
        if ((**i)["position_x"].getInt() == target_x &&
            (**i)["position_y"].getInt() == target_y &&
            ((**i)["level"] == mTom->property["level"]).isTrue())
            if ((**i)["enabled"].isTrue() && !(*i)->move(this))
            {
                mTom->mBeep->play();
                return false;
            }

    return true;
}

QList<MagicObject *> MagicMap::findDisplayObject(QString objectLabel, QString objectId, QList<QString> objectClass)
{
    QList<MagicObject *> objects;
    if (objectLabel == "global" || objectLabel == "map")
    {
        objects.append(this);
        return objects;
    }
    for (QList<MagicDisplayObject *>::iterator i = displayList.begin(); i != displayList.end(); i++)
    {
        /*qDebug() << (void *)(*i);
        qDebug() << (**i)["label"].getString();*/
        if ((objectLabel.isEmpty() || ((**i)["label"] == MagicVarient(objectLabel)).isTrue()) &&
                (objectId.isEmpty() || ((**i)["id"] == MagicVarient(objectId)).isTrue()) &&
                (objectClass.empty() || ((**i).inClass(objectClass))))
            objects.append(*i);
    }
    return objects;
}

void MagicMap::setProperty(QString propertyName, MagicVarient propertyValue)
{
    if (propertyName == "sound")
    {
        (new QSound(propertyValue.getString()))->play();
        return;
    }
    else if (propertyName == "print")
    {
        qDebug() << propertyValue.getString();
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

MagicTom *MagicMap::Tom()
{
    return this->mTom;
}
