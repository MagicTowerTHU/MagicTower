#include "magickey.h"

const int MagicKey::yellow = 0;
const int MagicKey::blue = 1;
const int MagicKey::red = 2;
const int MagicKey::silver = 3;

MagicKey::MagicKey(int x,int y, int color)
    : MagicInventory(x, y)
{
    property["label"] = "key";
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
