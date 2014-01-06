#ifndef MAGICEXPRESSION_H
#define MAGICEXPRESSION_H

#include "../magicmap.h"
#include "magicoperation.h"

#include <QStack>
#include <QFile>

class MagicExpression // forgot: why MagicHalt...
{
public:
    MagicExpression *next;
    MagicExpression();
    virtual void run(MagicMap *);
    virtual void setNext(MagicExpression *);

    static MagicExpression *input(QFile *, MagicMap *);

    static MagicDisplayObject *environment;
    static void setEnvironment(MagicDisplayObject *);
};

#endif // MAGICEXPRESSION_H
