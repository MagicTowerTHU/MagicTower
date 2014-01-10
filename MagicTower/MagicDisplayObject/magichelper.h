#ifndef MAGICHELPER_H
#define MAGICHELPER_H

#include "magicobject.h"

#include <QString>
#include <QHash>

class MagicHelper
{
    QHash<QString> alias;

public:
    MagicHelper();

    static MagicObject *createObject(QString);
};

#endif // MAGICHELPER_H
