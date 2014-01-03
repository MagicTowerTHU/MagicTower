#include "magicexpression.h"

#include <QTextStream>

MagicExpression::MagicExpression()
{
}

void MagicExpression::setNext(MagicExpression *next)
{
    this->next = next;
}

const int OPE_CNT = 11;
//						   +  -  *  /  %  ^   & << >>  ~   =
const int ope_order[OPE_CNT] = {5, 5, 4, 4, 4, 10, 9, 6, 6, 2, 15};
const int ope_assoc[OPE_CNT] = {0, 0, 0, 0, 0,  0, 0, 0, 0, 1,  1};

QStack<MagicOperand *> stackNum;
QStack<int> stackOpe, stackOrd;

void skipSpaces(QString buffer, int &p)
{
    while (buffer[p] == ' ' || buffer[p] = '\t') p++;
}

void operate()
{
    int ope = stackOpe.pop();
    switch (ope)
    {
    case 0: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "+")); break;
    case 1: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "-")); break;
    case 2: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "*")); break;
    case 3: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "/")); break;
    case 4: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "%")); break;
    case 5: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "^")); break;
    case 6: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "&")); break;
    case 7: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "<<")); break;
    case 8: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), ">>")); break;
    case 9: stackNum.push(new MagicOperation(stackNum.pop(), "~")); break;
    case 10: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "=")); break;
    }
}

bool isSymbol(char x)
{
    return !(x >= 'a' && x <= 'z' || x >= '0' && x <= '9' || x == '#' || x == '.');
}

MagicOperand *processLine(QString buffer)
{
    stackNum.clear(), stackOpe.clear(), stackOrd.clear();

    int t = 0;
    skipSpaces(buffer, t);

    int level = 0;

    while (buffer[t])
    {
        if (isSymbol(buffer[t]))
        {
            if (buffer[t] == '(')
            {
                t++, level++;
                skipSpaces(buffer, t);
                continue;
            }
            else if (buffer[t] == ')')
            {
                t++;
                if (--level < 0) throw "more ')' than '('!";
                skipSpaces(buffer, t);
                continue;
            }
            int ope = getOpe(buffer, t), order = (level << 5) - ope_order[ope];
            while (!stackOpe.empty() && order + ope_assoc[ope] <= stackOrd.top())
                operate();
            stackOpe.push(ope), stackOrd.push(order);
            skipSpaces(buffer, t);
        }else{
            stackNum.push(getInt(buffer, t));
            skipSpaces(buffer, t);
        }
    }

    while (!stackOpe.empty())
        operate();

    return stackNum[0];
}

static MagicExpression *MagicExpression::input(QFile *file)
{
    QStack<QHash<QString, MagicExpression *> > labelStack;

    stackNum.clear(), stackOpe.clear(), stackOrd.clear();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw "File Cannot Open...";

    MagicExpression *now = NULL, *first = NULL;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        MagicExpression *proceeded = processLine(line);
        if (!first)
            first = now = proceeded;
        else
            now->setNext(proceeded), now = proceeded;
    }
}
