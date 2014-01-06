#include "magicassignment.h"

#include <QtDebug>

MagicAssignment::MagicAssignment(MagicOperand *operand)
{
    next = NULL;
    this->operand = operand;
}

void MagicAssignment::run(MagicMap *map)
{
    operand->getValue(map);
    qDebug() << operand->getValue(map).getString();
    next->run(map);
}
