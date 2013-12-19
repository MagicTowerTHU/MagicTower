#ifndef MAGICOPERAND_H
#define MAGICOPERAND_H

#include "magicvarient.h"

class MagicOperand
{
public:
    MagicOperand();

    virtual MagicVarient getValue() = 0;
};

#endif // MAGICOPERAND_H
