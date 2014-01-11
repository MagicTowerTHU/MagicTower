#include "magictele.h"
#include "../magicmap.h"

MagicTele::MagicTele(MagicMap *parent, QString content)
    : MagicAnimate(parent)
{
    floor = new QPixmap(":/images/floor");
    wall = new QPixmap(":/images/wall");
    chosen = new QPixmap(":/images/chosen");
    this->content = content;
    xChoose = 2;
    yChoose = 4;
}

MagicTele::~MagicTele()
{
    delete floor;
    delete wall;
    delete chosen;
}

bool MagicTele::paint(QPainter *painter)
{
    if (wantDelete)
        return false;

    int offset = 16, margin_top = 20, margin_left = 10;
    for (int i = 1; i < 8; i++)
    {
        painter->drawPixmap(i*32 + offset, 2*32, *wall);
        painter->drawPixmap((i + 1)*32 + offset, 8*32, *wall);
    }
    for (int i = 2; i < 8; i++)
    {
        painter->drawPixmap(1*32 + offset, (i + 1)*32, *wall);
        painter->drawPixmap(8*32 + offset, i*32, *wall);
    }

    for (int i = 2; i < 8; i++)
        for (int j = 3; j < 8; j++)
            if (i == xChoose && j == yChoose)
                painter->drawPixmap(i*32 + offset, j*32, *chosen);
            else
                painter->drawPixmap(i*32 + offset, j*32, *floor);

    painter->setPen("white");
    painter->drawText(2*32 + offset + margin_left, 3*32 + margin_top, content);

    int k = 1;
    for (int j = 4; j < 8 && k != 22; j++)
        for (int i = 2; i < 8 && k != 22; i++)
        {
            painter->drawText(i*32 + offset + margin_left, j*32 + margin_top, QString::number(k));
            k++;
        }

    return true;
}

void MagicTele::input(int choice)
{
    switch (choice)
    {
    case Qt::Key_Up:
        if (yChoose - 1 >= 4)
            yChoose--;
        break;
    case Qt::Key_Down:
        if (yChoose + 1 <= 7)
            yChoose++;
        break;
    case Qt::Key_Left:
        if (xChoose - 1 >= 2)
            xChoose--;
        else if (yChoose - 1 >= 4)
        {
            yChoose--;
            xChoose = 7;
        }
        break;
    case Qt::Key_Right:
        if (xChoose + 1 <= 7)
            xChoose++;
        else if (yChoose + 1 <= 7)
        {
            yChoose++;
            xChoose = 2;
        }
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        int target = xChoose - 2 + (yChoose - 4) * 6 + 1;
        parent->Tom()->property["level"] = target;
        wantDelete = true;
        break;
    }
}
