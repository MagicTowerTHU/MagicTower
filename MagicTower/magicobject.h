#ifndef MAGICOBJECT_H
#define MAGICOBJECT_H

#include <QHash>
#include <QVariant>
#include <QObject>

class MagicObject : QObject
{
public:
    MagicObject();

    QHash<QString, QVariant> property;
};

#endif // MAGICOBJECT_H
