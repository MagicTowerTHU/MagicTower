#include "magicpopup.h"
#include "../magicmap.h"

MagicPopup::MagicPopup(MagicMap *parent, QString content)
    : MagicAnimate(parent)
{
    this->content = content;
    parent->appendSound(":/sounds/popup");
    background = QPixmap(":/images/chosen");
}

QRect MagicPopup::screen(1 * 32, 4 * 32 + 24, 9 * 32, 32 + 16);

bool MagicPopup::paint(QPainter *painter)
{
    painter->save();
    if (cnt < 10)
    {
        painter->setOpacity(cnt / 10.0);
    }
    else if (cnt < 30)
    {
        painter->setOpacity(1);
    }
    else if (cnt < 40)
    {
        painter->setOpacity((40 - cnt) / 10.0);
    }

    if (cnt < 40)
    {
        painter->setBrush(QBrush(background));
        painter->drawRect(screen);

        painter->setPen("black");
        painter->setFont(QFont("Arial", 15, 2));
        painter->drawText(screen, Qt::AlignCenter, content);
    }
    else
    {
        painter->restore();
        return false;
    }
    painter->restore();
    cnt++;
    return true;
}
