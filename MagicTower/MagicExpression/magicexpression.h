#ifndef MAGICEXPRESSION_H
#define MAGICEXPRESSION_H

#include "../magicmap.h"
#include "magicoperation.h"

#include <QStack>
#include <QFile>

class MagicExpression
{
    MagicExpression *next;
public:
    MagicExpression();
    virtual void run(MagicMap *);
    void setNext(MagicExpression *);
    static MagicExpression *input(QFile *);
};

#endif // MAGICEXPRESSION_H
