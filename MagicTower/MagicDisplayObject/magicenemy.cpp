#include "magicenemy.h"
#include "../magicmap.h"

#include <QPainter>
#include <QDebug>

MagicEnemy::MagicEnemy(int x, int y, int level, MagicMap *parent, QString name)
    : MagicDisplayObject(x, y, level, parent)
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

MagicEnemy::~MagicEnemy()
{
    delete pix[0];
    delete pix[1];
}

int MagicEnemy::damage(MagicMap *map)
{
    int kill = map->Tom()->property["attack"].getInt() - property["defend"].getInt();
    int casualty = property["attack"].getInt() - map->Tom()->property["defend"].getInt();
    int tomHealth = map->Tom()->property["health"].getInt();
    int enemyHealth = property["health"].getInt();
    int damage = 0;
    if (casualty <= 0) return 0;
    while (tomHealth > 0 && enemyHealth > 0)
    {
        tomHealth -= casualty;
        damage += casualty;
        enemyHealth -= kill;
    }
    return damage;
}

void MagicEnemy::paint(QPainter *painter)
{
    static int cnt = 12;
    painter->drawPixmap(x, y, cnt-- > 6 ? *pix[0] : *pix[1]);
    if (cnt <= 0) cnt = 12;
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
        property["enabled"] = 0;
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
            property["enabled"] = 0;
            return runAction(map, true);
        }
    }
}
