#ifndef MAGICREFERENCE_H
#define MAGICREFERENCE_H

#include "magicoperand.h"

#include <QString>
#include <QList>

class MagicReference : public MagicOperand
{
    QString objectLabel, objectId, property;
    QList<QString> objectClass;

public:
    MagicReference(QString, QString, QList<QString>, QString);

    virtual MagicVarient getValue(MagicMap *);
    MagicVarient setValue(MagicVarient, MagicMap *);
};

#endif // MAGICREFERENCE_H
