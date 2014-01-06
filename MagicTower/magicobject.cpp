#include "magicobject.h"

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
