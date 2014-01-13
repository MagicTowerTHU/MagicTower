#include "magickey.h"
#include "../MagicAnimate/magicpopup.h"

const int MagicKey::yellow = 0;
const int MagicKey::blue = 1;
const int MagicKey::red = 2;
const int MagicKey::silver = 3;

MagicKey::MagicKey(int x, int y, int level, MagicMap *parent, int color)
    : MagicInventory(x, y, level, parent)
{
    property["label"] = "key";
    appendClass("key");
    property["color"] = color;
    this->color = color;
    switch(color)
    {
    case yellow:
        pix = new QPixmap(":/images/key_yellow");
        break;
    case blue:
        pix = new QPixmap(":/images/key_blue");
        break;
    case red:
        pix = new QPixmap(":/images/key_red");
        break;
    default:
        pix = new QPixmap(":/images/key_silver"); // didn't find this kind of key...
        break;
    }
}

bool MagicKey::move(MagicMap *map)
{
    bool ret = MagicInventory::move(map);
    switch (color)
    {
    case yellow:
        parent->appendPopup("您获得了一把黄钥匙");
        break;
    case blue:
        parent->appendPopup("您获得了一把蓝钥匙");
        break;
    case red:
        parent->appendPopup("您获得了一把红钥匙");
        break;
    }
    return ret;
}

QString MagicKey::getLabel()
{
    return property["label"].getString() + "_" + QString::number(color);
}
