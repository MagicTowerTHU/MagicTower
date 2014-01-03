#include "magicoperation.h"
#include "magicreference.h"

MagicOperation::MagicOperation(MagicOperand *operand0, MagicOperand *operand1, QString mOperator)
{
    operand[0] = operand0, operand[1] = operand1, this->mOperator = mOperator;
}

MagicOperation::MagicOperation(MagicOperand *operand, QString mOperator) :
    MagicOperation(operand, NULL, mOperator)
{
}

MagicVarient MagicOperation::getValue(MagicMap *map)
{
    if (mOperator == "+")
        return (*operand[0])->getValue(map) + (*operand[1])->getValue(map);
    if (mOperator == "-")
        return (*operand[0])->getValue(map) - (*operand[1])->getValue(map);
    if (mOperator == "*")
        return (*operand[0])->getValue(map) * (*operand[1])->getValue(map);
    if (mOperator == "/")
        return (*operand[0])->getValue(map) / (*operand[1])->getValue(map);
    if (mOperator == "%")
        return (*operand[0])->getValue(map) % (*operand[1])->getValue(map);
    if (mOperator == "^")
        return (*operand[0])->getValue(map) ^ (*operand[1])->getValue(map);
    if (mOperator == "&")
        return (*operand[0])->getValue(map) & (*operand[1])->getValue(map);
    if (mOperator == "<<")
        return (*operand[0])->getValue(map) << (*operand[1])->getValue(map);
    if (mOperator == ">>")
        return (*operand[0])->getValue(map) >> (*operand[1])->getValue(map);
    if (mOperator == "~")
        return ~((*operand[0])->getValue(map));
    if (mOperator == "=")
    {
        MagicReference *x = dynamic_cast<MagicReference *>operand[0];
        if (!x)
            throw "Non-reference operand cannot be assigned any value.";
        x->setValue(operand[1]->getValue(map), map);
        return x->getValue(map);
    }
    throw "Invalid operation \"" + mOperator + "\"";
}
