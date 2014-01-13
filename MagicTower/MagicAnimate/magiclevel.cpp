#include "magiclevel.h"
#include "../magicmap.h"

MagicLevel::MagicLevel(MagicMap *parent, int level)
    : MagicAnimate(parent)
{
    this->buffer = "Level " + QString::number(level);
    this->level = level;
    parent->appendSound(":/sounds/level");
}

QRect MagicLevel::screen(0, 0, 352, 352);

bool MagicLevel::paint(QPainter *painter)
{
    painter->save();
    if (cnt < 10)
    {
        painter->setOpacity(cnt / 10.0);
        painter->setPen("black");
        painter->setBrush(Qt::SolidPattern);
        painter->drawRect(screen);
    }
    else if (cnt < 30)
    {
        painter->setPen("black");
        painter->setBrush(Qt::SolidPattern);
        painter->drawRect(screen);
        painter->setOpacity(((cnt - 10) / 20.0) * ((cnt - 10) / 20.0));

        painter->setPen("white");
        painter->setFont(QFont("Arial", 28, 10));
        painter->drawText(screen, Qt::AlignCenter, buffer);
    }
    else if (cnt < 50)
    {
        if (cnt == 30)
        {
            if (parent->Tom()->property["level"].getInt() > level)
            {
                for (QList<MagicDisplayObject *>::iterator i = parent->displayList.begin(); i != parent->displayList.end(); i++)
                    if ((**i)["label"].getString() == "destination_down" &&
                        (**i)["level"].getInt() == level)
                    {
                        int x = (**i)["position_x"].getInt(), y = (**i)["position_y"].getInt();
                        parent->Tom()->setProperty("position_x", x);
                        parent->Tom()->setProperty("position_y", y);
                    }
            }
            else
            {
                for (QList<MagicDisplayObject *>::iterator i = parent->displayList.begin(); i != parent->displayList.end(); i++)
                    if ((**i)["label"].getString() == "destination_up" &&
                        (**i)["level"].getInt() == level)
                    {
                        int x = (**i)["position_x"].getInt(), y = (**i)["position_y"].getInt();
                        parent->Tom()->setProperty("position_x", x);
                        parent->Tom()->setProperty("position_y", y);
                    }
            }
            parent->Tom()->property["level"] = level;
        }
        if (cnt == 31)
        {
            if (level == 0)
                parent->mBackSound->change(0);
            else if (level < 8)
                parent->mBackSound->change(1);
            else if (level < 15)
                parent->mBackSound->change(2);
            else if (level < 19)
                parent->mBackSound->change(3);
            else
                parent->mBackSound->change(4);
        }

        painter->setPen("black");
        painter->setBrush(Qt::SolidPattern);
        painter->drawRect(screen);
        painter->setOpacity(((50 - cnt) / 20.0) * ((50 - cnt) / 20.0));

        painter->setPen("white");
        painter->setFont(QFont("Arial", 28, 5));
        painter->drawText(screen, Qt::AlignCenter, buffer);
    }
    else if (cnt < 60)
    {
        painter->setOpacity((60 - cnt) / 10.0);
        painter->setPen("black");
        painter->setBrush(Qt::SolidPattern);
        painter->drawRect(screen);
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
