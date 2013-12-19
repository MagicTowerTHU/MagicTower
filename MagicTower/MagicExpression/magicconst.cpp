#include "magicconst.h"

MagicConst::MagicConst(MagicVarient v)
{
    value = v;
}

MagicVarient MagicConst::getValue()
{
    return this->value;
}
