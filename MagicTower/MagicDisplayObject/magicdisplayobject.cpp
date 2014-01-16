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
    property["picked"] = 0;
    property["enabled"] = 1;
    property["id"] = "";
}

MagicDisplayObject::~MagicDisplayObject()
{
    /*
    for (auto i = action.begin(); i != action.end(); i++)
        if (*i)
            delete *i;
    */
}

QString MagicDisplayObject::getLabel()
{
    return property["label"].getString();
}

void MagicDisplayObject::setProperty(QString propertyName, MagicVarient propertyValue, bool)
{
    if (propertyName == "position_x")
        x = propertyValue.getInt() * 32;
    if (propertyName == "position_y")
        y = propertyValue.getInt() * 32;
    if (propertyName == "label")
        return;
    if (propertyName == "drop")
    {
        MagicDisplayObject *nonConst = const_cast<MagicDisplayObject *>(this);
        nonConst->property["enabled"] = 0;
        nonConst->setProperty("picked", 0);
        return;
    }
    if (propertyName == "pick")
    {
        MagicDisplayObject *nonConst = const_cast<MagicDisplayObject *>(this);
        nonConst->setProperty("picked", 1);
        return;
    }
    if (propertyName == "picked")
    {
        if (propertyValue.isTrue())
        {
            property["enabled"] = 0;
            for (auto i = parent->Tom()->inventory.begin(); i != parent->Tom()->inventory.end(); i++)
                if ((*i)->getLabel() >= getLabel())
                {
                    parent->Tom()->inventory.insert(i, this);
                    goto exit;
                }
            parent->Tom()->inventory.append(this);
        }
        else
            parent->Tom()->inventory.removeAll(this);
    }
exit:
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
