#include "magiccondition.h"

MagicCondition::MagicCondition(MagicOperand *condition)
{
    this->condition = condition;
    trueBranch = falseBranch = NULL;
    next = NULL;
}

void MagicCondition::run(MagicMap *map)
{
    if (condition->getValue(map).isTrue())
        trueBranch->run(map);
    else
        falseBranch->run(map);
}

void MagicCondition::pushTrueBranch(MagicExpression *trueBranch)
{
    this->trueBranch = trueBranch;
}

void MagicCondition::pushFalseBranch(MagicExpression *falseBranch)
{
    this->falseBranch = falseBranch;
}

