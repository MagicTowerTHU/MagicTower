#include "magicdisplayobject.h"

#include <QPoint>

MagicDisplayObject::MagicDisplayObject()
{
    property["position"] = QPoint();
}
