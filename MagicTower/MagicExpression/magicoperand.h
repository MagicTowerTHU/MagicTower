#ifndef MAGICOPERAND_H
#define MAGICOPERAND_H

#include "magicvarient.h"
#include "../magicmap.h"

class MagicOperand
{
public:
    MagicOperand();

    virtual MagicVarient getValue(MagicMap *) = 0;
};

#endif // MAGICOPERAND_H
