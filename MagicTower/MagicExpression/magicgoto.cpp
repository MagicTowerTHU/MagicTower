#include "magicgoto.h"

MagicGoto::MagicGoto(QString label)
{
    this->label = label;
}

void MagicGoto::run(MagicMap *map)
{
    next->run(map);
}
