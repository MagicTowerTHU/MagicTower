#include "magicdisplayobject.h"
#include "../MagicExpression/magicexpression.h"
#include "../MagicExpression/magicvarient.h"

MagicDisplayObject::MagicDisplayObject(int x, int y, int level)
{
    property["position_x"] = x;
    property["position_y"] = y;
    property["level"] = level;
    this->x = x * 32, this->y = y * 32;
    property["enabled"] = 1;
    property["picked"] = 0;
    action = NULL;
}


MagicDisplayObject::~MagicDisplayObject()
{
    if (action)
        delete action;
}

void MagicDisplayObject::setAction(MagicExpression *action)
{
    this->action = action;
}

bool MagicDisplayObject::runAction(MagicMap *map, bool mask)
{
    auto ret = map->property.find("return");
    if (ret != map->property.end())
        map->property.erase(ret);
    MagicExpression::setEnvironment(this);
    if(action) action->run(map);
    MagicExpression::setEnvironment(NULL);
    if ((ret = map->property.find("return")) != map->property.end())
        return (*ret).isTrue();
    return mask;
}
