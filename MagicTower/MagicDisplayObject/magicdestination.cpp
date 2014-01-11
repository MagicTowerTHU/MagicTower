#include "magicdestination.h"

MagicDestination::MagicDestination(int x, int y, int level, int from)
    : MagicFloor(x, y, level)
{
    this->from = from;
    appendClass("destination");
    switch (name)
    {
    case 1:
        property["label"] = "destination_down";
        break;
    default -1;
        property["label"] = "destination_up";
        break;
    }
}
