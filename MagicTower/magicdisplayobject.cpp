#include "magicdisplayobject.h"
#include "MagicExpression/magicvarient.h"

MagicDisplayObject::MagicDisplayObject()
{
    property["position_x"] = MagicVarient(0);
    property["position_y"] = MagicVarient(0);
}

void MagicDisplayObject::setAction(MagicExpression *action)
{
    this->action = action;
}

bool MagicDisplayObject::move()
{
    return true;
}
