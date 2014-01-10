#include "magicreference.h"
#include "magicexpression.h"
#include "../magicobject.h"

#include <QList>

MagicReference::MagicReference(QString Label, QString Id, QList<QString> Class, QString property)
{
    objectLabel = Label, objectId = Id, objectClass = Class, this->property = property;
}

MagicVarient MagicReference::getValue(MagicMap *map)
{
    if (objectLabel == "this")
        return (*(MagicExpression::environment))[property];

    QList<MagicObject *>target = map->findDisplayObject(objectLabel, objectId, objectClass);
    if (!target.empty())
        return (*target.first())[property];
    else
    {
        QString err = "<MagicReference::getValue(MagicMap *)> Cannot find object : " + objectLabel + (objectId != "" ? "#" + objectId : "");// + (objectClass != "" ? "." + objectClass : "");
        throw err;
    }
}

MagicVarient MagicReference::setValue(MagicVarient x, MagicMap *map)
{
    if (objectLabel == "this")
    {
        (*(MagicExpression::environment))[property] = x;
        return x;
    }
    QList<MagicObject *>target = map->findDisplayObject(objectLabel, objectId, objectClass);
    if (!target.empty())
        for (QList<MagicObject *>::iterator i = target.begin(); i != target.end(); i++)
            (**i).setProperty(property, x);
    else
    {
        QString err = "<MagicReference::setValue(MagicMap *)> Cannot find object : " + objectLabel + (objectId != "" ? "#" + objectId : "");// + (objectClass != "" ? "." + objectClass : "");
        throw err;
    }
    return x;
}
