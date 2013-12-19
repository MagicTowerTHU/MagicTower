#include "magicassignment.h"

MagicAssignment::MagicAssignment()
{
    next = NULL;
}

void MagicAssignment::run(MagicMap *map)
{
    target->setValue(operand->getValue(map), map);
    next->run();
}
