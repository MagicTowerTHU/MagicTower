#include "magicreference.h"
#include "../magicobject.h"

#include <QList>

MagicReference::MagicReference(QString Label, QString Id, QList<QString> Class, QString property)
{
    objectLabel = Label, objectId = Id, objectClass = Class, this->property = property;
}

MagicVarient MagicReference::getValue(MagicMap *map)
{
    QList<MagicObject *>target = map->findObject(objectLabel, objectId, objectClass);
    if (!target.empty())
        return target.first()->getProperty(property);
    else
    {
        QString err = "<MagicReference::getValue(MagicMap *)> Cannot find object : " + objectLabel + (objectId != "" ? "#" + objectId : "");
        for (QList<QString>::iterator i = objectClass.begin(); i != objectClass.end(); i++)
            err += "." + (*i);
        throw err;
    }
}

void MagicReference::setValue(MagicVarient x, MagicMap *)
{
    QList<MagicObject *>target = map->findObject(objectLabel, objectId, objectClass);
    if (!target.empty())
        for (QList<MagicObject *>::iterator i = target.first(); i != target.end(); i++)
            (*i)->setProperty(property, x);
    else
    {
        QString err = "<MagicReference::setValue(MagicMap *)> Cannot find object : " + objectLabel + (objectId != "" ? "#" + objectId : "");
        for (QList<QString>::iterator i = objectClass.begin(); i != objectClass.end(); i++)
            err += "." + (*i);
        throw err;
    }
}
