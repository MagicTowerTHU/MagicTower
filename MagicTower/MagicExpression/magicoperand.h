#ifndef MAGICOPERAND_H
#define MAGICOPERAND_H

#include "magicvarient.h"
#include "../magicmap.h"

class MagicOperand
{
    MagicVarient *value;
public:
    MagicOperand();
    MagicOperand(MagicVarient);

    virtual MagicVarient getValue(MagicMap *);
};

#endif // MAGICOPERAND_H
