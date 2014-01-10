#ifndef MAGICOBJECT_H
#define MAGICOBJECT_H

#include "MagicExpression/magicvarient.h"

#include <QHash>
#include <QVariant>
#include <QObject>

class MagicObject : QObject
{
public:
    MagicObject();

    QHash<QString, MagicVarient> property;

    virtual MagicVarient &operator[](QString);
    virtual const MagicVarient &operator[](QString) const;
    virtual void setProperty(QString, MagicVarient);
};

#endif // MAGICOBJECT_H
