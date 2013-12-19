#include "magicoperation.h"

MagicOperation::MagicOperation(MagicOperand *operand0, MagicOperand *operand1)
{
    operand[0] = operand0, operand[1] = operand1;
}

MagicVarient MagicOperation::getValue()
{
    if (mOperator == "+")
        return *operand[0]->getValue() + *operand[1]->getValue();
    if (mOperator == "-")
        return *operand[0]->getValue() - *operand[1]->getValue();
    if (mOperator == "*")
        return *operand[0]->getValue() * *operand[1]->getValue();
    if (mOperator == "/")
        return *operand[0]->getValue() / *operand[1]->getValue();
    if (mOperator == "%")
        return *operand[0]->getValue() % *operand[1]->getValue();
    if (mOperator == "^")
        return *operand[0]->getValue() ^ *operand[1]->getValue();
    if (mOperator == "&")
        return *operand[0]->getValue() & *operand[1]->getValue();
    if (mOperator == "<<")
        return *operand[0]->getValue() << *operand[1]->getValue();
    if (mOperator == ">>")
        return *operand[0]->getValue() >> *operand[1]->getValue();
    if (mOperator == "~")
        return ~(*operand[0]->getValue());
    throw "Invalid operation \"" + mOperator + "\"";
}
