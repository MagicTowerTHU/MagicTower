#ifndef MAGICHELPER_H
#define MAGICHELPER_H

#include "magicdisplayobject.h"

#include <QString>
#include <QHash>

class MagicHelper
{
    static QHash<QString, QString> alias;

public:
    static MagicDisplayObject *createObject(QString, QString, QList<QString>, int, int, int);
};

#endif // MAGICHELPER_H
