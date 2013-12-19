#ifndef MAGICCONDITION_H
#define MAGICCONDITION_H

#include "magicexpression.h"
#include "magicoperand.h"

class MagicCondition : public MagicExpression
{
    MagicExpression *trueBranch, *falseBranch;
    MagicOperand *condition;

public:
    MagicCondition(MagicOperand *);
    virtual void run(MagicMap *);

    void pushTrueBranch(MagicExpression *);
    void pushFalseBranch(MagicExpression *);
};

#endif // MAGICCONDITION_H
