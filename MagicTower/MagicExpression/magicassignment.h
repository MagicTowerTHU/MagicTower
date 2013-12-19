#ifndef MAGICASSIGNMENT_H
#define MAGICASSIGNMENT_H

#include "magicexpression.h"

class MagicAssignment : public MagicExpression
{
public:
    MagicAssignment();
    virtual void run(MagicMap *map);
};

#endif // MAGICASSIGNMENT_H
