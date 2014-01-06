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

    MagicVarient &operator[](QString);
    const MagicVarient &operator[](QString) const;
    virtual void setProperty(QString, MagicVarient);
};

#endif // MAGICOBJECT_H
