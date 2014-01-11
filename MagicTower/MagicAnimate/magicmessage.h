#ifndef MAGICMESSAGE_H
#define MAGICMESSAGE_H

#include "magicanimate.h"

class MagicMessage : public MagicAnimate
{
    QString content;
    QPixmap *black, *wall, *upedge, *downedge, *rightedge, *leftedge, *rightupangle, *leftupangle, *rightdownangle, *leftdownangle;

public:
    MagicMessage(MagicMap *, QString);
    ~MagicMessage();
    virtual bool paint(QPainter *);
};

#endif // MAGICMESSAGE_H
