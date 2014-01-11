#include "magicdestination.h"

MagicDestination::MagicDestination(int x, int y, int level, int from)
    : MagicFloor(x, y, level)
{
    this->from = from;
    appendClass("destination");
    switch (from)
    {
    case 1:
        property["label"] = "destination_down";
        break;
    case 0:
        property["label"] = "destination_up";
        break;
    }
}
