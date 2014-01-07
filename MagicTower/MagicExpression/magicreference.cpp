#include "magicreference.h"
#include "magicexpression.h"
#include "../magicobject.h"

#include <QList>

MagicReference::MagicReference(QString Label, QString Id, QString Class, QString property)
{
    objectLabel = Label, objectId = Id.right(Id.length() - 1), objectClass = Class.right(Class.length() - 1), this->property = property;
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
        QString err = "<MagicReference::getValue(MagicMap *)> Cannot find object : " + objectLabel + (objectId != "" ? "#" + objectId : "") + (objectClass != "" ? "." + objectClass : "");
        throw err;
    }
}

void MagicReference::setValue(MagicVarient x, MagicMap *map)
{
    if (objectLabel == "this")
    {
        (*(MagicExpression::environment))[property] = x;
        return;
    }
    QList<MagicObject *>target = map->findDisplayObject(objectLabel, objectId, objectClass);
    if (!target.empty())
        for (QList<MagicObject *>::iterator i = target.begin(); i != target.end(); i++)
            (**i)[property] = x;
    else
    {
        QString err = "<MagicReference::setValue(MagicMap *)> Cannot find object : " + objectLabel + (objectId != "" ? "#" + objectId : "") + (objectClass != "" ? "." + objectClass : "");
        throw err;
    }
}
