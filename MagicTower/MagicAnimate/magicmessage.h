#ifndef MAGICMESSAGE_H
#define MAGICMESSAGE_H

#include "magicanimate.h"

class MagicMessage : public MagicAnimate
{
    QString content;
    QPixmap *black, *wall;

public:
    MagicMessage(MagicMap *, QString);
    ~MagicMessage();
    virtual bool paint(QPainter *);
};

#endif // MAGICMESSAGE_H
