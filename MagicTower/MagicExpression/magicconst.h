#ifndef MAGICCONST_H
#define MAGICCONST_H

#include "magicoperand.h"

class MagicConst : public MagicVarient
{
    MagicVarient value;

public:
    MagicConst(MagicVarient);
    virtual MagicVarient getValue();
};

#endif // MAGICCONST_H
