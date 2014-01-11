#include "magicmessage.h"

MagicMessage::MagicMessage(MagicMap *parent, QString content)
    : MagicAnimate(parent)
{
    this->content = content;
    black = new QPixmap(":/images/black");
    wall = new QPixmap(":/images/wall");
}

MagicMessage::~MagicMessage()
{
    delete black;
    delete wall;
}

bool MagicMessage::paint(QPainter *painter)
{
    if (wantDelete)
        return false;
    for (int i = 0; i < 10; i++)
    {
        painter->drawPixmap(i*32, 0, *wall);
        painter->drawPixmap((i+1)*32, 320, *wall);
        painter->drawPixmap(0, (i+1)*32, *wall);
        painter->drawPixmap(320, i*32, *wall);
    }
    for (int i = 1; i < 10; i++)
        for(int j = 1; j < 10; j++)
            painter->drawPixmap(i*32, j*32, *black);
}
