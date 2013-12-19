#include "magicassignment.h"

MagicAssignment::MagicAssignment()
{
}

void MagicAssignment::run(MagicMap *map)
{
    target->setValue(operand->getValue(map), map);
}
