#include "magiccondition.h"

MagicCondition::MagicCondition()
{
    trueBranch = falseBranch = NULL;
}

void MagicCondition::run(MagicMap *map)
{
}

void MagicCondition::pushTrueBranch(MagicExpression *trueBranch)
{
    this->trueBranch = trueBranch;
}

void MagicCondition::pushFalseBranch(MagicExpression *falseBranch)
{
    this->falseBranch = falseBranch;
}
