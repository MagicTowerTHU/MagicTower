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

QHash<QString, QString> MagicHelper::alias = QHash<QString, QString>();

MagicDisplayObject *MagicHelper::createObject(QString target, QString Id, QList<QString> Class, int x, int y, int level)
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
    }
    QRegExp rx("^([a-zA-Z0-9]*)(_(\\w*))?");
    rx.indexIn(target);

    QString category = rx.cap(1);
    QString detail = (rx.captureCount() >= 2) ? rx.cap(3) : "";
    if (alias.find(category) != alias.end())
        target = (category = alias[category]) + ((detail.isEmpty()) ? "" : "_" + detail);

    MagicDisplayObject *ret = NULL;
    if (category == "armour")
        ret = new MagicArmour(x, y, level, detail);
    else if (category == "door")
        ret = new MagicDoor(x, y, level, detail.toInt());
    else if (category == "enemy")
        ret = new MagicEnemy(x, y, level, detail);
    else if (category == "key")
        ret = new MagicKey(x, y, level, detail.toInt());
    else if (category == "up")
        ret = new MagicStairs(x, y, level, 1);
    else if (category == "down")
        ret = new MagicStairs(x, y, level, -1);
    else if (category == "tom")
        ret = new MagicTom(x, y, level);
    else if (category == "wall")
        ret = new MagicWall(x, y, level);
    else if (category == "weapon")
        ret = new MagicWeapon(x, y, level, detail);
    else
        throw "No such label...";

    ret->appendClass(Class);
    (*ret)["id"] = Id;

    return ret;
}
