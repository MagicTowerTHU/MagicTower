#include "magichelper.h"

#include "magicarmour.h"
#include "magicdoor.h"
#include "magicenemy.h"
#include "magicfloor.h"
#include "magickey.h"
#include "magicstairs.h"
#include "magictom.h"
#include "magicwall.h"
#include "magicweapon.h"

#include <QRegExp>

MagicHelper::MagicHelper()
{
    alias["a"] = "armour";
    alias["dr"] = "door";
    alias["e"] = "enemy";
    alias["k"] = "key";
    alias["up"] = "up";
    alias["dn"] = "down";
    alias["t"] = "tom";
    alias["w"] = "wall";
    alias["s"] = "weapon"; // sword
}

static MagicObject *MagicHelper::createObject(QString target, int x, int y)
{
    QRegExp rx("^(\\w*)?(#\\w*)?(.\\w*)?");
    rx.indexIn(target);

    QString category = rx.cap(1);
    QString detail = rx.cap(2);
    if (alias.find(tmp) != alias.end())
        target = category = alias[category] + "_" + ;

    if (category == "armour")
        return new MagicArmour(x, y, detail);
    else if (category == "door")
        return new MagicDoor(x, y, detail.toInt());
    else if (category == "enemy")
        return new MagicEnemy(x, y, detail);
    else if (category == "key")
        return new MagicKey(x, y, detail.toInt());
    else if (category == "up")
        return new MagicStairs(x, y, 1);
    else if (category == "down")
        return new MagicStairs(x, y, -1);
    else if (category == "tom")
        return new MagicTom(x, y);
    else if (category == "wall")
        return new MagicWall(x, y);
    else if (category == "weapon")
        return new MagicWeapon(x, y, detail);
}
