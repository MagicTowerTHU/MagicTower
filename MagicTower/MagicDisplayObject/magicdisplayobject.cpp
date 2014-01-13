#include "magicdisplayobject.h"
#include "../MagicExpression/magicexpression.h"
#include "../MagicExpression/magicvarient.h"

MagicDisplayObject::MagicDisplayObject(int x, int y, int level, MagicMap *parent)
{
    property["position_x"] = x;
    property["position_y"] = y;
    property["level"] = level;
    this->x = x * 32, this->y = y * 32;
    this->parent = parent;
    property["enabled"] = 1;
    property["picked"] = 0;
    property["id"] = "";
}

MagicDisplayObject::~MagicDisplayObject()
{
    for (auto i = action.begin(); i != action.end(); i++)
        if (*i)
            delete *i;
}

void MagicDisplayObject::setProperty(QString propertyName, MagicVarient propertyValue)
{
    if (propertyName == "position_x")
        x = propertyValue.getInt() * 32;
    if (propertyName == "position_y")
        y = propertyValue.getInt() * 32;
    if (propertyName == "picked" && propertyValue.isTrue())
        parent->Tom()->inventory.push_back(this);
    MagicObject::setProperty(propertyName, propertyValue);
}

void MagicDisplayObject::setAction(MagicExpression *action)
{
    this->action.append(action);
}

bool MagicDisplayObject::runAction(MagicMap *map, bool mask)
{
    map->property["return"] = mask;
    MagicExpression::setEnvironment(this);
    for (auto i = action.begin(); i != action.end(); i++)
        (*i)->run(map);
    MagicExpression::setEnvironment(NULL);
    return map->property["return"].getInt();
}
