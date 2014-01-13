#ifndef MAGICOBJECT_H
#define MAGICOBJECT_H

class MagicMap;

#include "MagicExpression/magicvarient.h"

#include <QHash>
#include <QSet>
#include <QVariant>
#include <QObject>
#include <QTextStream>

class MagicObject
{
    QSet<QString> mClass;

public:
    MagicObject();

    QHash<QString, MagicVarient> property;

    bool inClass(QString);
    bool inClass(QList<QString>);
    void appendClass(QString);
    void appendClass(QList<QString>);

    virtual MagicVarient &operator[](QString);
    virtual const MagicVarient &operator[](QString) const;
    virtual void setProperty(QString, MagicVarient, bool = true);

    void saveProperty(QTextStream *);
    void loadProperty(QTextStream *, MagicMap * = NULL);
};

#endif // MAGICOBJECT_H
