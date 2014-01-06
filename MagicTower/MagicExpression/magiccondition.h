#ifndef MAGICCONDITION_H
#define MAGICCONDITION_H

#include "magicexpression.h"
#include "magicoperand.h"

class MagicCondition : public MagicExpression
{
    MagicExpression *trueBranch, *falseBranch;
    MagicExpression *trueTail, *falseTail;
    MagicOperand *condition;

public:
    MagicCondition(MagicOperand *);
    virtual void run(MagicMap *);
    virtual void setNext(MagicExpression *);

    void pushTrueBranch(MagicExpression *, MagicExpression *);
    void pushFalseBranch(MagicExpression *, MagicExpression *);
};

#endif // MAGICCONDITION_H
