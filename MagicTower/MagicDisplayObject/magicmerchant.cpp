#include "magicmerchant.h"
#include "../magicmap.h"

#include <QStringList>

MagicMerchant::MagicMerchant(int x, int y, int level, QString name)
    : MagicDisplayObject(x, y, level)
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
    static int cnt = 120;
    painter->drawPixmap(x, y, cnt-- > 60 ? *pix[0] : *pix[1]);
    if (property["label"].getString() == "merchant_3")
    {
        painter->drawPixmap(x-32, y, QPixmap(":/images/merchant_3.2"));
        painter->drawPixmap(x+32, y, QPixmap(":/images/merchant_3.3"));
    }
    if (cnt <= 0) cnt = 120;

}

bool MagicMerchant::move(MagicMap *map)
{
    /*
    QStringList entries;
    entries.push_back("1. 翔");
    entries.push_back("2. 屎");
    entries.push_back("3. 便便");
    entries.push_back("4. 粑粑");
    entries.push_back("5. zhaojinxu");
    map->appendAnimate(new MagicInputBox(map, "同学你想吃什么呀~?", entries), false);
    */
    return runAction(map, false);
}
