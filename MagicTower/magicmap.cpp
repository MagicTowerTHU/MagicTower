#include "magicmap.h"
#include "MagicAnimate/magicanimate.h"
#include "MagicAnimate/magicmove.h"
#include "MagicAnimate/magicwisdom.h"
#include "MagicAnimate/magicmessage.h"
#include "MagicDisplayObject/magicenemy.h"
#include "MagicDisplayObject/magicstairs.h"
#include "MagicDisplayObject/magicwall.h"
#include "MagicDisplayObject/magicdoor.h"
#include "MagicDisplayObject/magickey.h"
#include "MagicDisplayObject/magicweapon.h"
#include "MagicDisplayObject/magicarmour.h"
#include "MagicDisplayObject/magicmedicine.h"

#include "MagicExpression/magicexpression.h"

#include <QPoint>
#include <QPointer>
#include <QSound>
#include <QDebug>
#include <QTextStream>
#include <QMediaObject>

#define yellow 0
#define blue 1
#define red 2
#define silver 3

MagicMap::MagicMap()
{
    animateTimer = new QTimer();

    initialize();

    mBackSound = new MagicBackSound();
    mBackSound->play(QSound::Infinite);
}

void MagicMap::destoryList()
{
    animateList.clear(), displayList.clear();
    /*
    for (auto i = animateList.begin(); i != animateList.end(); i++)
    {
        delete *i;
        i = animateList.erase(i);
    }
    for (auto i = displayList.begin(); i != displayList.end(); i++)
    {
        delete *i;
        i = displayList.erase(i);
    }*/
}

void MagicMap::initialize()
{
    mTom = new MagicTom(0, 0, 1);
    displayList.push_front(mTom);

    animateFlag = false;

    property["wisdomEnabled"] = 0;

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
                displayList.push_front(/*floor[11 * i + j] = */new MagicFloor(i, j, 1));

    for (int i = 12; i < 14; i++)
        for (int j = 0; j < 12; j++)
                displayList.push_front(/*inventory[12 * (i - 12) + j] = */new MagicFloor(j, i, 1));
}

bool MagicMap::loadMap(QFile *file)
{
    if (!file)
    {
        (*mTom)["position_x"] = 0;
        (*mTom)["position_y"] = 0;
        return false;
    }
    else
    {
        destoryList();

        initialize();

        try
        {
            MagicExpression::input(file, this)->run(this);
        }
        catch (const char *e)
        {
            qDebug() << "Exception: " << e;
            return false;
        }
        return true;
    }
}

bool MagicMap::saveRecord(QFile *file)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        printf("File Cannot Open..."), throw "File Cannot Open...";

    QTextStream out(file);

    out << MagicExpression::atList.length() + MagicExpression::onList.length() << endl;
    for (auto i = MagicExpression::atList.begin(); i != MagicExpression::atList.end(); i++)
        out << *i << endl;
    for (auto i = MagicExpression::onList.begin(); i != MagicExpression::onList.end(); i++)
        out << *i << endl;
    saveProperty(&out);
    for (auto i = displayList.begin(); i != displayList.end(); i++)
        (*i)->saveProperty(&out);

    return true;
}

bool MagicMap::loadRecord(QFile *file)
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        printf("File Cannot Open..."), throw "File Cannot Open...";

    QTextStream in(file);

    destoryList();

    initialize();

    /*
    int length = in.readLine().toInt();
    MagicExpression::atList.clear();
    for (int i = 0; i < length; i++)
        MagicExpression::atList.append(in.readLine());

    length = in.readLine().toInt();
    MagicExpression::onList.clear();
    for (int i = 0; i < length; i++)
        MagicExpression::onList.append(in.readLine());
*/
    MagicExpression::process(in, in.readLine().toInt(), this);

    loadProperty(&in);
    for (auto i = displayList.begin(); i != displayList.end(); i++)
        (*i)->loadProperty(&in, this);

    if (!in.atEnd())
        return false;

    return true;
}

void MagicMap::paint(QPainter *painter)
{
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
        if (e->key() == Qt::Key_L && property["wisdomEnabled"].isTrue())
            appendAnimate(new MagicWisdom(this), false);
        if (e->key() == Qt::Key_M)
            appendAnimate(new MagicMessage(this, "xfz是二逼.\n 赵锦煦也是"), false);
    }
    else
    {
        if (e->key() == Qt::Key_L && property["wisdomEnabled"].isTrue())
            for (auto i = animateList.begin(); i != animateList.end(); i++)
                if(MagicWisdom *wisdom = dynamic_cast<MagicWisdom *>(*i))
                    wisdom->wantDelete = true;
        if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
            for (auto i = animateList.begin(); i != animateList.end(); i++)
                if(MagicMessage *message = dynamic_cast<MagicMessage *>(*i))
                    message->wantDelete = true;
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
        QSound::play(":/sounds/beep");
        return false;
    }

    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((**i)["position_x"].getInt() == target_x &&
            (**i)["position_y"].getInt() == target_y &&
            ((**i)["level"] == mTom->property["level"]).isTrue())
            if ((**i)["enabled"].isTrue() && !(*i)->move(this))
            {
                QSound::play(":/sounds/beep");
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
        QSound::play(propertyValue.getString());
        return;
    }
    else if (propertyName == "print")
    {
        qDebug() << propertyValue.getString();
        return;
    }
    MagicObject::setProperty(propertyName, propertyValue);
}
/*
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
*/
MagicTom *MagicMap::Tom()
{
    return this->mTom;
}
