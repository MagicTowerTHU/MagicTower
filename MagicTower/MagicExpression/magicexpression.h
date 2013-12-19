#ifndef MAGICEXPRESSION_H
#define MAGICEXPRESSION_H

#include "magicmap.h"

class MagicExpression
{
public:
    MagicExpression();
    virtual void run(MagicMap *map) = 0;
};

#endif // MAGICEXPRESSION_H
