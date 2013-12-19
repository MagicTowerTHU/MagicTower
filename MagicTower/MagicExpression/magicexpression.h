#ifndef MAGICEXPRESSION_H
#define MAGICEXPRESSION_H

#include "../magicmap.h"

class MagicExpression
{
    MagicExpression *next;
public:
    MagicExpression();
    virtual void run(MagicMap *) = 0;
};

#endif // MAGICEXPRESSION_H
