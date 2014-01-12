#include "magicmerchant.h"
#include "../magicmap.h"

#include <QStringList>

MagicMerchant::MagicMerchant(int x, int y, int level, QString name, MagicMap *parent)
    : MagicDisplayObject(x, y, level, parent)
{
    property["label"] = "merchant_" + name;
    appendClass("merchant");
    pix[0] = new QPixmap(":/images/merchant_" + name + ".0");
    pix[1] = new QPixmap(":/images/merchant_" + name + ".1");

}

MagicMerchant::~MagicMerchant()
{
    delete pix[0];
    delete pix[1];
}

void MagicMerchant::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, cnt-- > 10 ? *pix[0] : *pix[1]);
    if (property["label"].getString() == "merchant_3")
    {
        painter->drawPixmap(x-32, y, QPixmap(":/images/merchant_3.2"));
        painter->drawPixmap(x+32, y, QPixmap(":/images/merchant_3.3"));
    }
    if (cnt <= 0) cnt = 20;

}

bool MagicMerchant::move(MagicMap *map)
{
    return runAction(map, false);
}
