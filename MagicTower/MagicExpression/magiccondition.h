#ifndef MAGICCONDITION_H
#define MAGICCONDITION_H

#include "magicexpression.h"

class MagicCondition : public MagicExpression
{
public:
    MagicCondition();
    virtual void run(MagicMap *map);
};

#endif // MAGICCONDITION_H
