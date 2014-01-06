#include "magicexpression.h"
#include "magicassignment.h"
#include "magicgoto.h"
#include "magiccondition.h"

#include <QTextStream>
#include <QChar>
#include <QtDebug>
#include <iostream>

MagicExpression::MagicExpression()
{
}

void MagicExpression::run(MagicMap *) // halt
{
    qDebug() << "MagicExpression::run() terminates";
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
    while (buffer[p] == ' ' || buffer[p] == '\t') p++;
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
    return !(x >= 'a' && x <= 'z' || x >= '0' && x <= '9' || x == '#' || x == '.' || x == '\"');
}

int getOpe(QString buffer, int &p)
{
    switch (buffer[p++].toLatin1())
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '%': return 4;
        case '^': return 5;
        case '&': return 6;
        case '<': if (buffer[p++] == '<') return 7; else throw "bad operator!";
        case '>': if (buffer[p++] == '>') return 8; else throw "bad operator!";
        case '~': return 9;
        default: throw "bad operator!";
    }
}

MagicOperand *getVar(QString buffer, int &p)
{
    /*if (!buffer[p].isDigit()) throw "bad number!";
    int result = 0;
    while (buffer[p].isDigit())
        result *= 10, result += buffer[p++].toLatin1() - '0';
    */
    if (buffer[p].isDigit() || buffer[p] == '\"')
        return new MagicOperand(MagicVarient::input(buffer, p));
    else
    {
        QRegExp rx("^(\\w*)?(#\\w*)?(.\\w*)?\\s*->\\s*(\\w*)");
        rx.indexIn(buffer, p);
        p += rx.captureCount();
        return new MagicReference(rx.cap(1), rx.cap(2), rx.cap(3), rx.cap(4));
    }
}

QList<MagicDisplayObject *> getObj(QString buffer, MagicMap *map)
{
    QRegExp rx("^(\\w*)?(#\\w*)?(.\\w*)?");
    rx.indexIn(buffer);
    return map->findDisplayObject(rx.cap(1), rx.cap(2), rx.cap(3));
}

MagicOperand *processLine(QString buffer)
{
    stackNum.clear(), stackOpe.clear(), stackOrd.clear();

    int t = 0;
    skipSpaces(buffer, t);

    int level = 0;

    while (t < buffer.length())
    {
        if (isSymbol(buffer[t].toLatin1()))
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
        } else {
            stackNum.push(getVar(buffer, t));
            skipSpaces(buffer, t);
        }
    }

    while (!stackOpe.empty())
        operate();

    return stackNum.pop();
}

MagicOperand *getCondition(QString buffer, int p)
{
    QRegExp rx("^\\s*\\((.*)\\)$");
    rx.indexIn(buffer.mid(2));
    return processLine(rx.cap(1));
}

QStack<QHash<QString, MagicExpression *>> labelStack;
QStack<QList<MagicGoto *>> gotoStack;

QStack<MagicExpression *>firstStack, nowStack;
QStack<int>ifFlagStack; // 0 nothing, 1 expecting expression, 2 expecting else, 3 expecting else expression.
int ifFlag;
QStack<MagicCondition *>ifStack;

QList<MagicDisplayObject *> targetObjects;
bool targetFlag;

MagicExpression *head;
MagicExpression *tail;

inline void newBlock()
{
    labelStack.push(QHash<QString, MagicExpression *>());
    gotoStack.push(QList<MagicGoto *>());
    firstStack.push(NULL);
    nowStack.push(NULL);
    ifFlagStack.push(ifFlag);
    ifFlag = 0;
}

inline void backBlock()
{
    for (auto i = targetObjects.begin(); i != targetObjects.end(); i++)
        (*i)->setAction(firstStack.top());
    for (auto i = gotoStack.top().begin(); i != gotoStack.top().end(); i++)
        (*i)->setNext(labelStack.top()[(*i)->label]->next);
    labelStack.pop();
    gotoStack.pop();
    head = firstStack.pop();
    tail = nowStack.pop();
    ifFlag = ifFlagStack.pop();
}

void singleLine()
{
    MagicExpression *savedHead = NULL, *savedTail = NULL;
    if (ifFlag == 2)
    {
        savedHead = head, savedTail = tail;
        head = tail = ifStack.pop();
    }
    ifFlag = 0;
    if (!firstStack.top()) // Oh no, goto should have another next entry...
        firstStack.top() = head, nowStack.top() = tail;
    else
        nowStack.top()->setNext(head), nowStack.top() = tail;

    if (!ifFlagStack.empty() && ifFlagStack.top() % 2) // closing this expression
    {
        backBlock();

        MagicCondition *condition = ifStack.top();
        if (!condition)
            throw "not a if block?!!";
        if (ifFlag == 1)
        {
            condition->pushTrueBranch(head, tail);
            ifFlag = 2;
        }
        if (ifFlag == 3)
        {
            condition->pushFalseBranch(head, tail);
            head = tail = ifStack.pop();
            singleLine(); // ifFlag => 0
        }
    }

    if (savedHead && savedTail)
    {
        head = savedHead;
        tail = savedTail;
        singleLine();
    }

    if (ifFlagStack.size() == 1 && targetFlag) // processing <on> block
    {
        backBlock();
        targetFlag = false;
        for (auto i = targetObjects.begin(); i != targetObjects.end(); i++)
            (*i)->setAction(head);
        tail->setNext(new MagicExpression());
        return;
    }
}

MagicExpression *MagicExpression::input(QFile *file, MagicMap *map)
{
    labelStack.clear();
    labelStack.push(QHash<QString, MagicExpression *>());
    gotoStack.clear();
    gotoStack.push(QList<MagicGoto *>());

    firstStack.clear();
    firstStack.push(NULL); nowStack.push(NULL);
    ifFlag = 0;

    targetFlag = false;

    stackNum.clear(), stackOpe.clear(), stackOrd.clear();

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        printf("File Cannot Open..."), throw "File Cannot Open...";

    QTextStream in(file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        try
        {
            if (line.startsWith("goto"))
                gotoStack.top().append(new MagicGoto(line.mid(4).trimmed()));
            else if (line.startsWith(":"))
            {
                labelStack.top()[line.mid(1).trimmed()] = nowStack.top();
                continue;
            }
            else if (line.startsWith("if"))
            {
                MagicOperand *condition = getCondition(line, 2);
                ifStack.push(new MagicCondition(condition));
                ifFlag = 1;
                newBlock();
                continue;
            }
            else if (line.startsWith("else"))
            {
                if (ifFlag == 2)
                {
                    ifFlag = 3;
                    newBlock();
                    continue;
                }
                else
                    throw "not expecting 'else'";
                continue;
            }
            else if (line.startsWith("on"))
            {
                if (firstStack.size() > 1)
                    throw "bad 'on' symbol: cannot be inside any blocks.";

                QRegExp rx("^\\s*\\((.*)\\)$");
                rx.indexIn(line.mid(2));
                targetObjects = getObj(rx.cap(1).trimmed(), map);
                targetFlag = true;
                newBlock();
                continue;
            }
            else if (line.startsWith("{"))
            {
                newBlock();
                continue;
            }
            else if (line.startsWith("}"))
            {
                backBlock();
            }
            else
            {
                head = tail = new MagicAssignment(processLine(line));
                //qDebug() << line << " => " << dynamic_cast<MagicAssignment *>(nowStack.top())->operand->getValue(NULL).getString() << endl;
            }

            // Processing single line;
            singleLine();
        }
        /*catch (const char *e)
        {
            qDebug() << "Exception : " << e;
        }*/
        catch (int x) {}
    }

    head = tail = new MagicExpression();
    singleLine();

    for (auto i = gotoStack.top().begin(); i != gotoStack.top().end(); i++)
        (*i)->setNext(labelStack.top()[(*i)->label]->next);

    gotoStack.pop();
    labelStack.pop();
    nowStack.pop();
    return firstStack.pop();
}
