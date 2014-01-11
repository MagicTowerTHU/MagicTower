#include "magicenemy.h"
#include "../magicmap.h"

#include <QPainter>
#include <QDebug>

MagicEnemy::MagicEnemy(int x, int y, int level, QString name)
    : MagicDisplayObject(x, y, level)
{
    property["label"] = "enemy_" + name;
    appendClass("enemy");
    pix[0] = new QPixmap(":/images/enemy_" + name + ".0");
    pix[1] = new QPixmap(":/images/enemy_" + name + ".1");
    switch(name.toInt())
    {
    case 1:
        property["attack"] = 10;
        property["defend"] = 100;
        property["health"] = 100;
        property["exp"] = 100;
        property["money"] = 100;
        break;
    case 2:
        property["attack"] = 80;
        property["defend"] = 200;
        property["health"] = 200;
        property["exp"] = 200;
        property["money"] = 200;
        break;
    case 3:
        property["attack"] = 230;
        property["defend"] = 100;
        property["health"] = 300;
        property["exp"] = 300;
        property["money"] = 300;
        break;
    case 4:
        property["attack"] = 200;
        property["defend"] = 130;
        property["health"] = 400;
        property["exp"] = 400;
        property["money"] = 400;
        break;
    case 5:
        property["attack"] = 100;
        property["defend"] = 200;
        property["health"] = 500;
        property["exp"] = 500;
        property["money"] = 500;
        break;
    default:
        property["attack"] = 70;
        property["defend"] = 100;
        property["health"] = 16000;
        property["exp"] = 600;
        property["money"] = 600;
        break;
    }
}

void MagicEnemy::paint(QPainter *painter)
{
    static int cnt = 120;
    painter->drawPixmap(x, y, cnt-- > 60 ? *pix[0] : *pix[1]);
    if (cnt <= 0) cnt = 120;
}

bool MagicEnemy::move(MagicMap *map)
{
    qDebug() << property["label"].getString() <<
                property["attack"].getInt() <<
                property["defend"].getInt() <<
                property["health"].getInt();
    if (map->Tom()->property["attack"].getInt() <= property["defend"].getInt())
    {
        qDebug() << "can't break defence!!";
        return runAction(map, false);
    }
    else if(map->Tom()->property["defend"].getInt() >= property["attack"].getInt())
    {
        qDebug() << "Tom health left:" << map->Tom()->property["health"].getInt();
        map->Tom()->property["exp"] += property["exp"].getInt();
        map->Tom()->property["money"] += property["money"].getInt();
        map->eraseMapObject(property["label"].getString(), property["position_x"].getInt(), property["position_y"].getInt());
        return runAction(map, true);
    }
    else
    {
        int kill = map->Tom()->property["attack"].getInt() - property["defend"].getInt();
        int casualty = property["attack"].getInt() - map->Tom()->property["defend"].getInt();
        int tomHealth = map->Tom()->property["health"].getInt();
        int enemyHealth = property["health"].getInt();
        while (tomHealth > 0 && enemyHealth > 0)
        {
            tomHealth -= casualty;
            enemyHealth -= kill;
        }
        if(tomHealth <= 0)
        {
            qDebug() << "will die!!";
            return runAction(map, false);
        }
        else
        {
            map->Tom()->property["health"] = tomHealth;
            map->Tom()->property["exp"] += property["exp"].getInt();
            map->Tom()->property["money"] += property["money"].getInt();
            qDebug() << "Tom health left:" << map->Tom()->property["health"].getInt();
            map->eraseMapObject(property["label"].getString(), property["position_x"].getInt(), property["position_y"].getInt());
            return runAction(map, true);
        }
    }
}
