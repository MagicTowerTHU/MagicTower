#include "magictom.h"
#include "magickey.h"

#include "../MagicAnimate/magiclevel.h"

#include <QBitmap>
#include <QDebug>

QString Pix_string[4][3] = {  {":/images/Tom_face1", ":/images/Tom_face2", ":/images/Tom_face"},
                              {":/images/Tom_left1", ":/images/Tom_left2", ":/images/Tom_left"},
                              {":/images/Tom_back1", ":/images/Tom_back2", ":/images/Tom_back"},
                              {":/images/Tom_right1", ":/images/Tom_right2", ":/images/Tom_right"}};

MagicTom::MagicTom(int x, int y, int level, MagicMap *parent)
    : MagicDisplayObject(x, y, level, parent)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            Pix[i][j] = new QPixmap(Pix_string[i][j]);

    MagicKey *p;
    for(int i = 0; i < 100; i++)
    {
        p = new MagicKey(5, 5, 0, parent, 0);
        p->property["enabled"] = 0;
        backupKey0.push_back(p);
        p = new MagicKey(5, 5, 0, parent, 1);
        p->property["enabled"] = 0;
        backupKey1.push_back(p);
        p = new MagicKey(5, 5, 0, parent, 2);
        p->property["enabled"] = 0;
        backupKey2.push_back(p);
    }

    pix = Pix[0][2];

    property["label"] = "tom";
    property["attack"] = 50;
    property["defend"] = 50;
    property["health"] = 500;
    property["exp"] = 0;
    property["money"] = 0;
    property["id"] = "";
    property["range"] = 0;

    //qDebug() <<"Tom: "<< property["attack"].getInt() << property["defend"].getInt() << property["health"].getInt();
    //qDebug() <<"Tom: "<< property["label"].getString() << property["level"].getInt() << property["id"].getString();
}

void MagicTom::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicTom::move(MagicMap *)
{
    return true;
}

void MagicTom::setProperty(QString propertyName, MagicVarient propertyValue, bool block)
{
    if (propertyName == "add_K")
    {
        int iteration = propertyValue.getInt();
        for (int i = 0; i < iteration; i++)
            switch (propertyValue.getInt())
            {
            case 0:
                backupKey0.takeFirst()->setProperty("pick", 1);
                break;
            case 1:
                backupKey1.takeFirst()->setProperty("pick", 1);
                break;
            case 2:
                backupKey2.takeFirst()->setProperty("pick", 1);
                break;
            }
        return;
    }
    if (propertyName == "level")
    {
        int level = propertyValue.getInt();

        if (parent->eventFlag)
        {
            parent->appendAnimate(new MagicLevel(parent, level), block);
        }
        else
        {
            MagicDisplayObject::setProperty(propertyName, propertyValue);
            if (level == 0)
                parent->mBackSound->change(0);
            else if (level < 8)
                parent->mBackSound->change(1);
            else if (level < 15)
                parent->mBackSound->change(2);
            else if (level < 19)
                parent->mBackSound->change(3);
            else
                parent->mBackSound->change(4);
        }

        if (propertyValue.getInt() > property["range"].getInt())
            property["range"] = propertyValue.getInt();

        return;
    }
    MagicDisplayObject::setProperty(propertyName, propertyValue);
}

MagicVarient &MagicTom::operator[](QString propertyName)
{
    if (propertyName.startsWith("get_K"))
    {
        return *(new MagicVarient(const_cast<MagicTom *>(this)->consumeInventory("key", propertyName.at(5).cell() - '0')));
    }
    return MagicDisplayObject::operator [](propertyName);
}

const MagicVarient &MagicTom::operator[](QString propertyName) const
{
    if (propertyName.startsWith("get_K"))
    {
        return *(new MagicVarient(const_cast<MagicTom *>(this)->consumeInventory("key", propertyName.at(5).cell() - '0')));
    }
    return MagicDisplayObject::operator [](propertyName);
}

void MagicTom::changePic(int direction, int duration)
{
    if (duration > 0)
        pix = Pix[direction][(duration / 4) % 2];
    else
        pix = Pix[direction][2];
}


bool MagicTom::haveInventory(QString label)
{
    for (auto i = inventory.begin(); i != inventory.end(); i++)
        if ( ((**i)["label"] == MagicVarient(label)).isTrue() )
            return true;
    return false;
}

bool MagicTom::consumeInventory(QString label)
{
    for (auto i = inventory.begin(); i != inventory.end(); i++)
        if ( ((**i)["label"] == MagicVarient(label)).isTrue() )
        {
            (*i)->setProperty("drop", 1);
            return true;
        }
    return false;
}

bool MagicTom::consumeInventory(QString label, int color)
{
    for (auto i = inventory.begin(); i != inventory.end(); i++)
        if ( ((**i)["label"] == MagicVarient(label)).isTrue() &&
             ((**i)["color"] == MagicVarient(color)).isTrue() )
        {
            (*i)->setProperty("drop", 1);
            return true;
        }
    return false;
}
