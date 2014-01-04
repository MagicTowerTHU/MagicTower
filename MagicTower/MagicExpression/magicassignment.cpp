#include "magicassignment.h"

MagicAssignment::MagicAssignment(MagicOperand *operand)
{
    next = NULL;
    this->operand = operand;
}

void MagicAssignment::run(MagicMap *map)
{
    operand->getValue(map);
    next->run(map);
}
