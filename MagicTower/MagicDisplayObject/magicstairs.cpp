#include "magicstairs.h"
#include "../magicmap.h"

MagicStairs::MagicStairs(int x, int y, int level, int direction)
    : MagicFloor(x, y, level)
{
    property["label"] = "stairs";
    appendClass("stairs");
    this->direction = direction;
    if(direction == 1)
        pix = new QPixmap(":/images/upstairs");
    else
        pix = new QPixmap(":/images/downstairs");
}

bool MagicStairs::move(MagicMap *map)
{
    switch(direction)
    {
    case 1:
        map->Tom()->setProperty("level", map->Tom()->property["level"] + 1);
        for (QList<MagicDisplayObject *>::iterator i = map->displayList.begin(); i != map->displayList.end(); i++)
            if ((**i)["level"].getInt() == map->Tom()->property["level"].getInt() &&
                (**i)["label"].getString() == "destination_up")
            {
                int x = (**i)["position_x"].getInt(), y = (**i)["position_y"].getInt();
                map->Tom()->setProperty("position_x", x);
                map->Tom()->setProperty("position_y", y);
            }
        break;
    default:
        map->Tom()->setProperty("level", map->Tom()->property["level"] - 1);
        for (QList<MagicDisplayObject *>::iterator i = map->displayList.begin(); i != map->displayList.end(); i++)
            if ((**i)["level"].getInt() == map->Tom()->property["level"].getInt() &&
                (**i)["label"].getString() == "destination_down")
            {
                int x = (**i)["position_x"].getInt(), y = (**i)["position_y"].getInt();
                map->Tom()->setProperty("position_x", x);
                map->Tom()->setProperty("position_y", y);
            }
        break;
    }
    return runAction(map, false);
}
