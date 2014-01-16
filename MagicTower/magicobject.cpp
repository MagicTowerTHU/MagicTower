#include "magicobject.h"
#include "MagicExpression/magicvarient.h"
#include "magicmap.h"

#include <QDebug>

MagicObject::MagicObject()
{
}

MagicVarient &MagicObject::operator[](QString propertyName)
{
    return property[propertyName];
}

const MagicVarient &MagicObject::operator[](QString propertyName) const
{
    return property.find(propertyName).value();
}

void MagicObject::setProperty(QString propertyName, MagicVarient propertyValue, bool)
{
    property[propertyName] = propertyValue;
}

bool MagicObject::inClass(QString c)
{
    return mClass.contains(c);
}

bool MagicObject::inClass(QList<QString> c)
{
    for (auto i = c.begin(); i != c.end(); i++)
        if (!mClass.contains(*i))
            return false;
    return true;
}

void MagicObject::appendClass(QList<QString> c)
{
    for (auto i = c.begin(); i != c.end(); i++)
        mClass.insert(*i);
}

void MagicObject::appendClass(QString c)
{
    mClass.insert(c);
}

void MagicObject::saveProperty(QTextStream *out)
{
    *out << property.size() << endl;
    for (QHash<QString, MagicVarient>::iterator i = property.begin(); i != property.end(); i++)
        *out << i.key() << ':' << i.value().getOutput() << endl;
}

/*
void MagicObject::loadProperty(QTextStream *in, MagicMap *map)
{
    int length = in->readLine().toInt();
    for (int i = 0; i < length; i++)
    {
        QRegExp rx("^(.*):(.*)$");
        rx.indexIn(in->readLine());
        property[rx.cap(1)] = MagicVarient::setInput(rx.cap(2));
        if (rx.cap(1) == "picked" && rx.cap(2) != "0")
            map->Tom()->inventory.push_back(dynamic_cast<MagicDisplayObject *>(this));
        else if (rx.cap(1) == "position_x")
            dynamic_cast<MagicDisplayObject *>(this)->x = rx.cap(2).toInt() * 32;
        else if (rx.cap(1) == "position_y")
            dynamic_cast<MagicDisplayObject *>(this)->y = rx.cap(2).toInt() * 32;
    }
}*/

void MagicObject::loadProperty(QTextStream *in, MagicMap *)
{
    int length = in->readLine().toInt();
    for (int i = 0; i < length; i++)
    {
        QRegExp rx("^(\\w*):(.*)$");
        rx.indexIn(in->readLine());
        setProperty(rx.cap(1), MagicVarient::setInput(rx.cap(2)));
    }
}
