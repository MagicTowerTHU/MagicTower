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

void MagicCondition::setNext(MagicExpression *next)
{
    this->next = next;
    trueTail->setNext(next);
    falseTail->setNext(next);
}

void MagicCondition::pushTrueBranch(MagicExpression *branch, MagicExpression *tail)
{
    trueBranch = branch;
    trueTail = tail;
}

void MagicCondition::pushFalseBranch(MagicExpression *branch, MagicExpression *tail)
{
    falseBranch = branch;
    falseTail = tail;
}
