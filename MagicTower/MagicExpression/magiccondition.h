#ifndef MAGICCONDITION_H
#define MAGICCONDITION_H

#include "magicexpression.h"

class MagicCondition : public MagicExpression
{
    MagicExpression *trueBranch, *falseBranch;

public:
    MagicCondition();
    virtual void run(MagicMap *);

    void pushTrueBranch(MagicExpression *);
    void pushFalseBranch(MagicExpression *);
};

#endif // MAGICCONDITION_H
