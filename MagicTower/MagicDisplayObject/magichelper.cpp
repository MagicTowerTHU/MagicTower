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
#include "magicmedicine.h"
#include "magicwit.h"
#include "magicmerchant.h"
#include "magicteleport.h"
#include "magicdestination.h"
#include "magicaltwall.h"
#include "magicany.h"
#include "magicfloor.h"

#include "../magicmap.h"

#include <QRegExp>

QHash<QString, QString> MagicHelper::alias = QHash<QString, QString>();

MagicDisplayObject *MagicHelper::createObject(QString target, QString Id, QList<QString> Class, int x, int y, int level, MagicMap *map)
{
    static bool isFirstTime = 1;
    if (isFirstTime)
    {
        isFirstTime = 0;
        MagicHelper::alias.clear();
        alias["a"] = "armour";
        alias["dr"] = "door";
        alias["e"] = "enemy";
        alias["k"] = "key";
        alias["up"] = "up";
        alias["dn"] = "down";
        alias["t"] = "tom";
        alias["w"] = "wall";
        alias["s"] = "weapon"; // sword
        alias["m"] = "medicine";
        alias["wi"] = "wit";
        alias["me"] = "merchant";
        alias["te"] = "teleport";
        alias["d"] = "destination";
        alias["aw"] = "altwall";
        alias["an"] = "any";
        alias["f"] = "floor";
    }
    QRegExp rx("^([a-zA-Z0-9]*)(_(\\S*))?");
    rx.indexIn(target);

    QString category = rx.cap(1);
    QString detail = (rx.captureCount() >= 2) ? rx.cap(3) : "";
    if (alias.find(category) != alias.end())
        target = (category = alias[category]) + ((detail.isEmpty()) ? "" : "_" + detail);

    MagicDisplayObject *ret = NULL;
    if (category == "armour")
        ret = new MagicArmour(x, y, level, detail, map);
    else if (category == "door")
        ret = new MagicDoor(x, y, level, map, detail.toInt());
    else if (category == "enemy")
        ret = new MagicEnemy(x, y, level, map, detail);
    else if (category == "key")
        ret = new MagicKey(x, y, level, map, detail.toInt());
    else if (category == "up")
        ret = new MagicStairs(x, y, level, map, 1);
    else if (category == "down")
        ret = new MagicStairs(x, y, level, map, -1);
    else if (category == "tom")
    {
        map->Tom()->setProperty("position_x", x);
        map->Tom()->setProperty("position_y", y);
        map->Tom()->setProperty("level", level);
    }
    else if (category == "wall")
        ret = new MagicWall(x, y, level, map);
    else if (category == "weapon")
        ret = new MagicWeapon(x, y, level, detail, map);
    else if (category == "medicine")
        ret = new MagicMedicine(x, y, level, detail, map);
    else if (category == "wit")
        ret = new MagicWit(x, y, level, map);
    else if (category == "merchant")
        ret = new MagicMerchant(x, y, level, detail, map);
    else if (category == "teleport")
        ret = new MagicTeleport(x, y, level, map);
    else if (category == "destination")
        ret = new MagicDestination(x, y, level, detail.toInt(), map);
    else if (category == "altwall")
        ret = new MagicAltWall(x, y, level, map, detail);
    else if (category == "any")
        ret = new MagicAny(x, y, level, map);
    else if (category == "floor")
        ret = new MagicFloor(x, y, level, map);
    else
        throw "No such label...";

    if (ret)
    {
        ret->appendClass(Class);
        (*ret)["id"] = Id;
    }

    return ret;
}
