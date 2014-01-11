#include "magicwisdom.h"
#include "../MagicDisplayObject/magicenemy.h"

MagicWisdom::MagicWisdom(MagicMap *parent)
    : MagicAnimate(parent)
{
    floor = new QPixmap(":/images/floor");
    wall = new QPixmap(":/images/wall");
}

MagicWisdom::~MagicWisdom()
{
    delete floor;
    delete wall;
}

bool MagicWisdom::paint(QPainter *painter)
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
            painter->drawPixmap(i*32, j*32, *floor);

    // painter->drawText(0, 20, QString("MagicTom"));
    int k = 0, l = 1;
    l++;
    painter->drawText(l*23 +4, k*32+17+4, QString("attack")); l+=2;
    painter->drawText(l*23 +4, k*32+17+4, QString("defend")); l+=2;
    painter->drawText(l*23 +4, k*32+17+4, QString("health")); l+=2;
    painter->drawText(l*23 +4, k*32+17+4, QString("exp")); l+=2;
    painter->drawText(l*23 +4, k*32+17+4, QString("money")); l+=2;
    painter->drawText(l*23 +4, k*32+17+4, QString("damage")); l+=2;
    /*
    QList<QString> enemySet;
    for (auto i = parent->displayList.begin(); i != parent->displayList.end(); i++)
        if (MagicEnemy *enemy = dynamic_cast<MagicEnemy *>(*i))
            if (!enemySet.contains(enemy->property["label"].getString()))
            {
                enemySet.push_back(enemy->property["label"].getString());

            }
*/
    return true;
}
