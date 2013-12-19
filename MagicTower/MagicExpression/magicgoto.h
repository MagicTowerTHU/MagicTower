#ifndef MAGICGOTO_H
#define MAGICGOTO_H

#include "magicexpression.h"

class MagicGoto : public MagicExpression
{
public:
    MagicGoto(MagicExpression *);
    virtual void run(MagicMap *);
};

#endif // MAGICGOTO_H
