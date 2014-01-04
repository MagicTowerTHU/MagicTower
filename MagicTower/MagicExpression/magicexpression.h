#ifndef MAGICEXPRESSION_H
#define MAGICEXPRESSION_H

#include "../magicmap.h"
#include "magicoperation.h"

#include <QStack>
#include <QFile>

class MagicExpression
{
protected:
    MagicExpression *next;
public:
    MagicExpression();
    virtual void run(MagicMap *) = 0;
    void setNext(MagicExpression *);
    static MagicExpression *input(QFile *);
};

#endif // MAGICEXPRESSION_H
