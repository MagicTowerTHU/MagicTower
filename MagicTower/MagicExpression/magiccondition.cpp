#include "magiccondition.h"

#include <QDebug>

MagicCondition::MagicCondition(MagicOperand *condition)
{
    this->condition = condition;
    trueBranch = falseBranch = NULL;
    next = NULL;
}

void MagicCondition::run(MagicMap *map)
{
    if (condition->getValue(map).isTrue())
    {
        if (trueBranch)
            trueBranch->run(map);
    }
    else
    {
        if (falseBranch)
            falseBranch->run(map);
    }
}

void MagicCondition::setNext(MagicExpression *next)
{
    this->next = next;
    trueTail->setNext(next);
    if (falseBranch)
        falseTail->setNext(next);
    else
        falseBranch = next;
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
