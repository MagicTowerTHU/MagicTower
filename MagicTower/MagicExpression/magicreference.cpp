#include "magicreference.h"
#include "../magicobject.h"

#include <QList>

MagicReference::MagicReference(QString Label, QString Id, QString Class, QString property)
{
    objectLabel = Label, objectId = Id, objectClass = Class, this->property = property;
}

MagicVarient MagicReference::getValue(MagicMap *map)
{
    QList<MagicObject *>target = map->findObject(objectLabel, objectId, objectClass);
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
    QList<MagicObject *>target = map->findObject(objectLabel, objectId, objectClass);
    if (!target.empty())
        for (QList<MagicObject *>::iterator i = target.begin(); i != target.end(); i++)
            (**i)[property] = x;
    else
    {
        QString err = "<MagicReference::setValue(MagicMap *)> Cannot find object : " + objectLabel + (objectId != "" ? "#" + objectId : "") + (objectClass != "" ? "." + objectClass : "");
        throw err;
    }
}
