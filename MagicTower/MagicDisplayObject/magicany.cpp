#include "magicany.h"

MagicAny::MagicAny(int x, int y, int level, MagicMap *parent)
    : MagicDisplayObject(x, y, level, parent)
{
    this->setProperty("pix", MagicVarient(":/images/keythree"));
    property["label"] = "any";
}

MagicAny::~MagicAny()
{
    delete pix;
}

#include <QDebug>

void MagicAny::setProperty(QString propertyName, MagicVarient propertyValue)
{
    if (propertyName == "pix")
        pix = new QPixmap(propertyValue.getString());
    //qDebug() << propertyName << ":" << propertyValue.getString();
    MagicDisplayObject::setProperty(propertyName, propertyValue);
}

void MagicAny::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

bool MagicAny::move(MagicMap *map)
{
    return runAction(map, true);
}
