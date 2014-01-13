#include "magicwisdom.h"
#include "../MagicDisplayObject/magicenemy.h"


MagicWisdom::MagicWisdom(MagicMap *parent)
    : MagicAnimate(parent)
{
    black = new QPixmap(":/images/floor");
    wall = new QPixmap(":/images/wall");
}

MagicWisdom::~MagicWisdom()
{
    delete black;
    delete wall;
}

bool MagicWisdom::paint(QPainter *painter)
{
    painter->setPen("white");
    cnt--;
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

    // painter->drawText(0, 20, QString("MagicTom"));
    int k = 1, l = 1, offset = 20, margin_left = 32, margin_top = 17;
    l++;
    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString("攻击")); l+=2;
    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString("防御")); l+=2;
    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString("生命")); l+=2;
    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString("经验")); l+=2;
    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString("金钱")); l+=2;
    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString("伤害")); l+=2;
    k++;
    QList<QString> enemySet;
    for (auto i = parent->displayList.begin(); i != parent->displayList.end(); i++)
        if (MagicEnemy *enemy = dynamic_cast<MagicEnemy *>(*i))
            if (!enemySet.contains(enemy->property["label"].getString()) &&
                parent->Tom()->property["level"].getInt() == enemy->property["level"].getInt() &&
                enemy->property["enabled"].isTrue())
            {
                enemySet.push_back(enemy->property["label"].getString());
                painter->drawPixmap(32, k*32, cnt > 10 ? *(enemy->pix[0]) : *(enemy->pix[1]));
                l = 2;
                painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString::number(enemy->property["attack"].getInt())); l+=2;
                painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString::number(enemy->property["defend"].getInt())); l+=2;
                painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString::number(enemy->property["health"].getInt())); l+=2;
                painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString::number(enemy->property["exp"].getInt())); l+=2;
                painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString::number(enemy->property["money"].getInt())); l+=2;
                int damage = enemy->damage(parent);
                if (damage < 0)
                    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString("???"));
                else if (damage >= parent->Tom()->property["health"].getInt())
                {
                    painter->setPen("red");
                    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString::number(damage));
                    painter->setPen("white");
                }
                else
                    painter->drawText(l*offset + margin_left +4, k*32+margin_top+4, QString::number(damage));
                l+=2;
                k++;
            }

    if(cnt <= 0) cnt = 20;
    return true;
}
