#ifndef MAGICHELPER_H
#define MAGICHELPER_H

#include "magicobject.h"

#include <QString>
#include <QHash>

class MagicHelper
{
    static QHash<QString, QString> alias;

public:
    static MagicObject *createObject(QString, int, int);
};

#endif // MAGICHELPER_H
