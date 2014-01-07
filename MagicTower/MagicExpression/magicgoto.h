#ifndef MAGICGOTO_H
#define MAGICGOTO_H

#include "magicexpression.h"

class MagicGoto : public MagicExpression
{
public:
    QString label;
    MagicGoto(QString);
    //virtual void run(MagicMap *);
};

#endif // MAGICGOTO_H
