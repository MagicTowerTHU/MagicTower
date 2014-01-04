#ifndef MAGICREFERENCE_H
#define MAGICREFERENCE_H

#include "magicoperand.h"

#include <QString>
#include <QList>

class MagicReference : public MagicOperand
{
    QString objectLabel, objectId, objectClass, property;

public:
    MagicReference(QString, QString, QString, QString);

    virtual MagicVarient getValue(MagicMap *);
    void setValue(MagicVarient, MagicMap *);
};

#endif // MAGICREFERENCE_H
