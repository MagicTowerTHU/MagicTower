#include "magicdisplayobject.h"
#include "../MagicExpression/magicexpression.h"
#include "../MagicExpression/magicvarient.h"

MagicDisplayObject::MagicDisplayObject()
{
    property["position_x"] = 0;
    property["position_y"] = 0;
    property["enabled"] = 1;
    action = NULL;
}

void MagicDisplayObject::setAction(MagicExpression *action)
{
    this->action = action;
}

int MagicDisplayObject::runAction(MagicMap *map)
{
    auto ret = map->property.find("return");
    if (ret != map->property.end())
        map->property.erase(ret);
    MagicExpression::setEnvironment(this);
    if(!action) action->run(map);
    MagicExpression::setEnvironment(NULL);
    if ((ret = map->property.find("return")) != map->property.end())
        return (*ret).isTrue();
    return -1;
}
