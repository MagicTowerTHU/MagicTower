#include "magicgoto.h"

MagicGoto::MagicGoto(MagicExpression *target)
{
    this->target = target;
}

void MagicGoto::run(MagicMap *map)
{
    target->run(map);
}
