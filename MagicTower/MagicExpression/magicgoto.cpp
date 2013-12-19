#include "magicgoto.h"

MagicGoto::MagicGoto(MagicExpression *target)
{
    setNext(target);
}

void MagicGoto::run(MagicMap *map)
{
    next->run(map);
}
