#include "magicaltwall.h"

MagicAltWall::MagicAltWall(int x, int y, int level, MagicMap *parent, QString name)
    : MagicWall(x, y, level, parent)
{
    property["label"] = "altwall_" + name;
    pix = new QPixmap(":/images/altwall_" + name);
}

void MagicAltWall::paint(QPainter *painter)
{
    painter->save();
    painter->translate(x, y);
    if (--cnt > 10)
    {
        painter->translate(32, 0);
        painter->scale(-1, 1);
    }
    painter->drawPixmap(0, 0, *pix);
    painter->restore();
    if (cnt < 0) cnt = 20;
}
