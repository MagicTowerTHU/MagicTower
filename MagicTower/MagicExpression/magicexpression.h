#ifndef MAGICEXPRESSION_H
#define MAGICEXPRESSION_H

#include "../magicmap.h"
#include "magicoperation.h"

#include <QStack>
#include <QFile>
#include <QStringList>
#include <QTextStream>

class MagicExpression // forgot: why MagicHalt...
{
    static void goForIt(QString, MagicMap *, QTextStream *);

public:
    MagicExpression *next;
    MagicExpression();
    virtual void run(MagicMap *);
    virtual void setNext(MagicExpression *);

    static MagicExpression *input(QFile *, MagicMap *);

    static MagicDisplayObject *environment;
    static void setEnvironment(MagicDisplayObject *);

    static QStringList onList, atList;
};

#endif // MAGICEXPRESSION_H
