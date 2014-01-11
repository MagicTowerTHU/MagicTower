#ifndef MAGICINPUTBOX_H
#define MAGICINPUTBOX_H

#include "magicanimate.h"

#include <QStringList>

class MagicInputBox : public MagicAnimate
{
    QString content;
    QStringList entries;
    QPixmap *black, *wall, *upedge, *downedge, *rightedge, *leftedge, *rightupangle, *leftupangle, *rightdownangle, *leftdownangle, *leftmiddle, *rightmiddle, *middle;

public:
    MagicInputBox(MagicMap *, QString, QStringList);
    void input(int);
    virtual bool paint(QPainter *);
};

#endif // MAGICINPUTBOX_H
