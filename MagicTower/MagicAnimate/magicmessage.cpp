#include "magicmessage.h"

MagicMessage::MagicMessage(MagicMap *parent, QString content)
    : MagicAnimate(parent)
{
    this->content = content;
    black = new QPixmap(":/images/black");
    wall = new QPixmap(":/images/wall");
    rightedge = new QPixmap(":/images/right_edge");
    rightdownangle = new QPixmap(":/images/rightdown_angle");
    rightupangle = new QPixmap(":/images/rightup_angle");
    leftedge = new QPixmap(":/images/left_edge");
    leftdownangle = new QPixmap(":/images/leftdown_angle");
    leftupangle = new QPixmap(":/images/leftup_angle");
    upedge = new QPixmap(":/images/up_edge");
    downedge = new QPixmap(":/images/down_edge");
}

MagicMessage::~MagicMessage()
{
    delete black;
    delete wall;
    delete rightedge;
    delete rightdownangle;
    delete rightupangle;
    delete leftedge;
    delete leftdownangle;
    delete leftupangle;
    delete upedge;
    delete downedge;
}

bool MagicMessage::paint(QPainter *painter)
{
    if (wantDelete)
        return false;

    painter->save();
    painter->setOpacity(0.8);

    painter->drawPixmap(1*32, 2*32, *leftupangle);
    painter->drawPixmap(9*32, 2*32, *rightupangle);
    painter->drawPixmap(1*32, 8*32, *leftdownangle);
    painter->drawPixmap(9*32, 8*32, *rightdownangle);
    for(int i = 2; i <= 8; i++)
    {
        painter->drawPixmap(i*32, 2*32, *upedge);
        painter->drawPixmap(i*32, 8*32, *downedge);
    }
    for(int i = 3; i <= 7; i++)
    {
        painter->drawPixmap(1*32, i*32, *leftedge);
        painter->drawPixmap(9*32, i*32, *rightedge);
    }

    for (int i = 2; i <= 8; i++)
        for(int j = 3; j <= 7; j++)
            painter->drawPixmap(i*32, j*32, *black);

    int margin_top = 17;
    painter->setPen("white");
    painter->setFont(QFont("黑体", 14));
    painter->setOpacity(1);
    painter->drawText(QRect(3*32, margin_top + 3*32, 5*32, 3*32 + 16), content);

    painter->restore();

    return true;
}
