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
};

#endif // MAGICOBJECT_H
