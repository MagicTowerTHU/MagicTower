#include "magicoperand.h"

MagicOperand::MagicOperand()
{
    value = NULL;
}

MagicOperand::MagicOperand(MagicVarient value)
{
    this->value = new MagicVarient(value);
}

MagicVarient MagicOperand::getValue(MagicMap *map)
{
    if (value) return *value;
    throw "orz";
}
