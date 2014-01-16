#include "magicmap.h"
#include "MagicAnimate/magicanimate.h"
#include "MagicAnimate/magicmove.h"
#include "MagicAnimate/magicwisdom.h"
#include "MagicAnimate/magicmessage.h"
#include "MagicAnimate/magicinputbox.h"
#include "MagicAnimate/magictele.h"
#include "MagicDisplayObject/magicenemy.h"
#include "MagicDisplayObject/magicstairs.h"
#include "MagicDisplayObject/magicwall.h"
#include "MagicDisplayObject/magicdoor.h"
#include "MagicDisplayObject/magickey.h"
#include "MagicDisplayObject/magicweapon.h"
#include "MagicDisplayObject/magicarmour.h"
#include "MagicDisplayObject/magicmedicine.h"

#include "MagicExpression/magicexpression.h"
#include "MagicAnimate/magicpopup.h"

#include <QPoint>
#include <QPointer>
#include <QSound>
#include <QDebug>
#include <QTextStream>
#include <QMediaObject>
#include <QMutableListIterator>

#define yellow 0
#define blue 1
#define red 2
#define silver 3

#include <QThread>
#include <QMutex>

MagicMap::MagicMap()
{
    animateTimer = new QTimer();

    initialize();

    mBackSound = new MagicBackSound();
    mBackSound->play(QSound::Infinite);
}

void MagicMap::destoryList()
{
    animateListLock.lockForWrite();
    animateList.clear(), displayList.clear();
    animateListLock.unlock();
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
    mTom = new MagicTom(0, 0, 1, this);
    displayList.push_front(mTom);

    animateFlag = 0;
    eventFlag = 0;

    property["wisdomEnabled"] = 0;
    property["teleportEnabled"] = 0;

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
                displayList.push_front(/*floor[11 * i + j] = */new MagicFloor(i, j, 100, this));

    for (int i = 12; i <= 14; i++)
        for (int j = 0; j < 11; j++)
                displayList.push_front(/*inventory[12 * (i - 12) + j] = */new MagicFloor(j, i, 100, this));
}

bool MagicMap::loadMap(QString fileName)
{
    if (fileName.isEmpty())
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
            MagicExpression *global = MagicExpression::input(fileName, this);
            if (global)
                global->run(this);
            else
                return false;
        }
        catch (const char *e)
        {
            qDebug() << "Exception: " << e;
            return false;
        }
        catch (QString x)
        {
            qDebug() << "Exception: " << x;
            return false;
        }

        return true;
    }
}

bool MagicMap::saveRecord(QFile *file)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        throw "File Cannot Open...";

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
        throw "File Cannot Open...";

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
    {
        qDebug() << "File should not end here...";
        return false;
    }

    return true;
}

void MagicMap::paint(QPainter *painter)
{
    soundListLock.lock();
    for (QMutableListIterator<QString> i(soundToPlay); i.hasNext(); )
    {
        QSound::play(i.next());
        i.remove();
    }
    soundListLock.unlock();

    for (auto i = displayList.begin(); i != displayList.end(); i++)
        if ((**i)["enabled"].isTrue() &&
            (((**i)["level"] == mTom->property["level"]).isTrue() || (**i)["level"].getInt() == 100))
            (*i)->paint(painter);
    mTom->paint(painter);

    int j = 0;
    for (auto i = mTom->inventory.begin(); i != mTom->inventory.end(); i++)
    {
        int x = j % 11;
        int y = j / 11 + 12;
        (**i)["position_x"] = x, (**i)["position_y"] = y;
        (*i)->x = x * 32, (*i)->y = y * 32;
        (*i)->paint(painter);
        j++;
    }

    animateListLock.lockForWrite();
    for (QMutableListIterator<MagicAnimate *> i(animateList); i.hasNext(); )
        if (i.next()->paint(painter) == false)
        {
            i.value()->lock();
            i.value()->wakeAll();
            i.value()->unlock();
            if (dynamic_cast<MagicPopup *>(i.value()) == NULL)
                animateFlag--;
            i.remove();
        }
    animateListLock.unlock();
}

void MagicMap::appendPopup(QString content, bool block)
{
    appendAnimate(new MagicPopup(this, content), block);
}

class AppendThread : public QThread
{
    MagicAnimate *target;
    MagicMap *parent;

public:
    AppendThread(MagicMap *parent, MagicAnimate *target)
    {
        this->parent = parent;
        this->target = target;
    }

    void run()
    {
        parent->animateListLock.lockForWrite();
        if (dynamic_cast<MagicPopup *>(target) == NULL)
            parent->animateFlag++;
        parent->animateList.append(target);
        parent->animateListLock.unlock();
    }
};

void MagicMap::appendAnimate(MagicAnimate *animate, bool block)
{
    if (!block)
    {
        AppendThread *appendThread = new AppendThread(this, animate);
        appendThread->start();
        QObject::connect(appendThread, SIGNAL(finished()), appendThread, SLOT(deleteLater()));
        return;
    }
    animate->lock();
    animateListLock.lockForWrite();
    if (dynamic_cast<MagicPopup *>(animate) == NULL)
        animateFlag++;
    animateList.append(animate);
    animateListLock.unlock();
    animate->wait(animate);
    animate->unlock();
}

void MagicMap::appendObject(MagicDisplayObject *target)
{
    if (!target)
        throw "What are you doing?";
    displayList.push_back(target);
}

void MagicMap::appendSound(QString target)
{
    soundListLock.lock();
    soundToPlay.append(target);
    soundListLock.unlock();
}

class KeyThread : public QThread
{
    MagicMap *parent;
    int key;

    static const int moveDuration = 4;

public:
    KeyThread(MagicMap *parent, QKeyEvent *e)
    {
        this->parent = parent;
        key = e->key();
        parent->eventFlag++;
    }

    ~KeyThread()
    {
        parent->eventFlag--;
    }

    void run()
    {
        if (!parent->animateFlag)
        {
            switch (key)
            {
            case Qt::Key_Down:
                parent->Tom()->changePic(0,0);
                if (parent->move(0, 1))
                    parent->appendAnimate(new MagicMove(parent, 0, 1, parent->Tom(), moveDuration), false);
                break;
            case Qt::Key_Left:
                parent->Tom()->changePic(1,0);
                if (parent->move(1, 1))
                    parent->appendAnimate(new MagicMove(parent, 1, 1, parent->Tom(), moveDuration), false);
                break;
            case Qt::Key_Up:
                parent->Tom()->changePic(2,0);
                if (parent->move(2, 1))
                    parent->appendAnimate(new MagicMove(parent, 2, 1, parent->Tom(), moveDuration), false);
                break;
            case Qt::Key_Right:
                parent->Tom()->changePic(3,0);
                if (parent->move(3, 1))
                    parent->appendAnimate(new MagicMove(parent, 3, 1, parent->Tom(), moveDuration), false);
                break;
            default:
                break;
            }
            if (key == Qt::Key_L && parent->property["wisdomEnabled"].isTrue())
                parent->appendAnimate(new MagicWisdom(parent), false);

            if (key == Qt::Key_T && parent->property["teleportEnabled"].isTrue())
                parent->appendAnimate(new MagicTele(parent), false);

            if (key == Qt::Key_M) //for test
                parent->appendAnimate(new MagicMessage(parent, "xfz是二逼.\n 赵锦煦也是"), false);

        }
        else
        {
            parent->animateListLock.lockForRead();
            if (key == Qt::Key_L && parent->property["wisdomEnabled"].isTrue())
                for (auto i = parent->animateList.begin(); i != parent->animateList.end(); i++)
                    if(MagicWisdom *wisdom = dynamic_cast<MagicWisdom *>(*i))
                        wisdom->wantDelete = true;
            if (key == Qt::Key_Enter || key == Qt::Key_Return)
                for (auto i = parent->animateList.begin(); i != parent->animateList.end(); i++)
                    if(MagicMessage *message = dynamic_cast<MagicMessage *>(*i))
                        message->wantDelete = true;
            for (auto i = parent->animateList.begin(); i != parent->animateList.end(); i++)
            {
                MagicInputBox *inputbox = dynamic_cast<MagicInputBox *>(*i);
                if(inputbox)
                {
                    if (key == Qt::Key_Escape)
                        inputbox->wantDelete = true;
                    else
                        inputbox->input(key);
                }
            }
            for (auto i = parent->animateList.begin(); i != parent->animateList.end(); i++)
                if(MagicTele *tele = dynamic_cast<MagicTele *>(*i))
                {
                    if (key == Qt::Key_T)
                        tele->wantDelete = true;
                    else
                        tele->input(key);
                }
            parent->animateListLock.unlock();
        }
    }
};

void MagicMap::keyPressEvent(QKeyEvent *e)
{
    KeyThread *keyThread = new KeyThread(this, e);
    keyThread->start();
    QObject::connect(keyThread, SIGNAL(finished()), keyThread, SLOT(deleteLater()));
}

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

bool MagicMap::move(int direction, int distance)
{
    int target_x = (*mTom)["position_x"].getInt() + dx[direction] * distance,
        target_y = (*mTom)["position_y"].getInt() + dy[direction] * distance;

    if (target_x < 0 || target_x > 10 || target_y < 0 || target_y > 10)
    {
        this->appendSound(":/sounds/beep");
        return false;
    }

    for (QList<MagicDisplayObject *>::iterator i = displayList.begin(); i != displayList.end(); i++)
        if ((**i)["position_x"].getInt() == target_x &&
            (**i)["position_y"].getInt() == target_y &&
            ((**i)["level"] == mTom->property["level"]).isTrue())
            if ((**i)["enabled"].isTrue()  && !(*i)->move(this))
            {
                return false;
            }

    this->appendSound(":/sounds/step");

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
        if (    (objectLabel.isEmpty() || ((**i)["label"] == MagicVarient(objectLabel)).isTrue()) &&
                (objectId.isEmpty() || ((**i)["id"] == MagicVarient(objectId)).isTrue()) &&
                (objectClass.empty() || ((**i).inClass(objectClass))))
            objects.append(*i);
    }
    return objects;
}

void MagicMap::setProperty(QString propertyName, MagicVarient propertyValue, bool)
{
    if (propertyName == "sound")
    {
        appendSound(getResource(propertyValue.getString()));
        return;
    }
    if (propertyName == "backsound")
    {
        mBackSound->change(propertyValue.getInt());
        return;
    }
    else if (propertyName == "print")
    {
        qDebug() << propertyValue.getString();
        return;
    }
    else if (propertyName == "message")
    {
        appendAnimate(new MagicMessage(this, propertyValue.getString()), true);
        return;
    }
    else if (propertyName == "popup")
    {
        appendPopup(propertyValue.getString());
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

void MagicMap::setPath(QString path)
{
    mapPath = path;
}

QString MagicMap::getResource(QString file)
{
    if (file.startsWith(":") || file.startsWith("/"))
        return file;
    else
        return mapPath + file;
}
