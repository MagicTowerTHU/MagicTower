#include "magicobject.h"

#include <QDebug>

MagicObject::MagicObject()
{
}

MagicVarient& MagicObject::operator[](QString propertyName)
{
    return property[propertyName];
}

const MagicVarient& MagicObject::operator[](QString propertyName) const
{
    return property[propertyName];
}

void MagicObject::setProperty(QString propertyName, MagicVarient propertyValue)
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
