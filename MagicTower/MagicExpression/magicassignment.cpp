#include "magicassignment.h"

MagicAssignment::MagicAssignment()
{
    next = NULL;
}

void MagicAssignment::run(MagicMap *map)
{
    operand->getValue(map);
    next->run();
}
