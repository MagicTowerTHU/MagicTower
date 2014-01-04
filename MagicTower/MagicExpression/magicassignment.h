#ifndef MAGICASSIGNMENT_H
#define MAGICASSIGNMENT_H

#include "magicexpression.h"
#include "magicreference.h"
#include "magicoperand.h"

class MagicAssignment : public MagicExpression
{

public:
    MagicOperand *operand;
    MagicAssignment(MagicOperand *);
    virtual void run(MagicMap *);
};

#endif // MAGICASSIGNMENT_H
