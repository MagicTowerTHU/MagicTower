#include "magicaltwall.h"

MagicAltWall::MagicAltWall(int x, int y, int level, MagicMap *parent, QString name)
    : MagicWall(x, y, level, parent)
{
    property["label"] = "altwall_" + name;
    pix = new QPixmap(":/images/altwall_" + name);
}
