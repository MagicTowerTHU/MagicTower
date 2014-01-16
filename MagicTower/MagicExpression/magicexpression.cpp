#include "magicexpression.h"
#include "magicassignment.h"
#include "magicgoto.h"
#include "magiccondition.h"
#include "../MagicDisplayObject/magichelper.h"
#include "../MagicDisplayObject/magicfloor.h"

#include <QTextStream>
#include <QChar>
#include <QStringList>
#include <QtDebug>
#include <iostream>

MagicExpression::MagicExpression()
{
    next = NULL;
}

void MagicExpression::run(MagicMap *map) // halt
{
    if (!next)
        //qDebug() << "MagicExpression::run() terminates";
        ;
    else
        next->run(map);
}

void MagicExpression::setNext(MagicExpression *next)
{
    this->next = next;
}

const int OPE_CNT = 17;
//                              0              5               10             15
//						        +  -  *  /  %  ^   & << >>  ~   =  < <=  > >= == !=
const int ope_order[OPE_CNT] = {5, 5, 4, 4, 4, 10, 9, 6, 6, 2, 15, 6, 6, 6, 6, 7, 7};
const int ope_assoc[OPE_CNT] = {0, 0, 0, 0, 0,  0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0};

QStack<MagicOperand *> stackNum;
QStack<int> stackOpe, stackOrd;

void skipSpaces(QString buffer, int &p)
{
    while (buffer[p] == ' ' || buffer[p] == '\t') p++;
}

void operate()
{
    int ope = stackOpe.pop();
    stackOrd.pop();
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
    case 11: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "<")); break;
    case 12: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "<=")); break;
    case 13: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), ">")); break;
    case 14: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), ">=")); break;
    case 15: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "==")); break;
    case 16: stackNum.push(new MagicOperation(stackNum.pop(), stackNum.pop(), "!=")); break;
    }
}

bool isSymbol(char x)
{
    return !((x >= 'a' && x <= 'z') || (x >= '0' && x <= '9') || x == '#' || x == '.' || x == '\"');
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
    case '<':
        if (buffer[p] == '<')
        {
            p++;
            return 7;
        }
        else if (buffer[p] == '=')
        {
            p++;
            return 12;
        }
        else
            return 11;
    case '>':
        if (buffer[p] == '>')
        {
            p++;
            return 8;
        }
        else if (buffer[p] == '=')
        {
            p++;
            return 14;
        }
            return 13;
    case '~': return 9;
    case '=':
        if (buffer[p] == '=')
        {
            p++;
            return 15;
        }
        else
            return 10;
    case '!':
        if (buffer[p++] == '=')
            return 16;
    default: throw "bad operator!";
    }

    return 0;
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
        QRegExp rx("^(\\w*)?(#\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?->\\s*(\\w*)");
        if (rx.indexIn(buffer.mid(p)) >= 0)
        {
            QList<QString> c;
            for (int i = 3; i < rx.captureCount(); i++)
                if (!rx.cap(i).isEmpty())
                    c.append(rx.cap(i).mid(1));
            p += rx.matchedLength();
            return new MagicReference(rx.cap(1), rx.cap(2).mid(1), c, rx.cap(9));
        }
        else
        {
            rx.setPattern("(\\w*)\\s*(\\((.*)\\))?");
            if (rx.indexIn(buffer.mid(p)) >= 0)
            {
                p += rx.matchedLength();
                if (rx.cap(1) == "input")
                    return new MagicReference("input", "", QList<QString>(), rx.cap(3));
                return new MagicReference("global", "", QList<QString>(), rx.cap(1));
            }
            throw "What variable?";
        }
    }
    return NULL;
}

QList<MagicObject *> getObj(QString buffer, MagicMap *map)
{
    QRegExp rx("^(\\w*)?(#\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?");
    rx.indexIn(buffer);
    QList<QString> c;
    for (int i = 3; i <= rx.captureCount(); i++)
        if (!rx.cap(i).isEmpty())
            c.append(rx.cap(i).mid(1));
    return map->findDisplayObject(rx.cap(1), rx.cap(2).mid(1), c);
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
            while (!stackOpe.empty() && (order + ope_assoc[ope] <= stackOrd.top()))
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

MagicOperand *getCondition(QString buffer, int)
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

QList<MagicObject *> targetObjects;
bool targetFlag; // <on> block flag
QStringList MagicExpression::onList;
QStringList MagicExpression::atList;
bool preprocessing;

MagicExpression *head;
MagicExpression *tail;

inline void newBlock(bool label = false)
{
    if (label)
    {
        labelStack.push(QHash<QString, MagicExpression *>());
        gotoStack.push(QList<MagicGoto *>());
    }
    firstStack.push(NULL);
    nowStack.push(NULL);
    ifFlagStack.push(ifFlag);
    ifFlag = 0;
}

inline void backBlock(bool label = false)
{
    if (label)
    {
        for (auto i = gotoStack.top().begin(); i != gotoStack.top().end(); i++)
        {
            auto position = labelStack.top().find((*i)->label);
            if (position == labelStack.top().end())
                throw "symbol not found :'" + (*i)->label + "'";
            (*i)->setNext((*position)->next);
        }
        labelStack.pop();
        gotoStack.pop();
    }
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
        backBlock(true);
        targetFlag = false;
        if (!preprocessing)
            for (auto i = targetObjects.begin(); i != targetObjects.end(); i++)
                dynamic_cast<MagicDisplayObject *>(*i)->setAction(head);
        tail->setNext(new MagicExpression());
        return;
    }
}

void MagicExpression::goForIt(QString line, MagicMap *map, QTextStream *pIn)
{
    if (line.startsWith("goto"))
    {
        head = tail = new MagicGoto(line.mid(4).trimmed());
        gotoStack.top().append(dynamic_cast<MagicGoto *>(head));
    }
    else if (line.startsWith(":"))
    {
        labelStack.top()[line.mid(1).trimmed()] = nowStack.top();
        return;
    }
    else if (line.startsWith("if"))
    {
        if (ifFlag == 2)
        {
            ifFlag = 0;
            head = tail = ifStack.pop();
            singleLine();
        }
        MagicOperand *condition = getCondition(line, 2);
        ifStack.push(new MagicCondition(condition));
        ifFlag = 1;
        newBlock();
        return;
    }
    else if (line.startsWith("else"))
    {
        if (ifFlag == 2)
        {
            ifFlag = 3;
            newBlock();
            return;
        }
        else
            throw "not expecting 'else'";
        return;
    }
    else if (line.startsWith("on"))
    {
        if (preprocessing)
            onList.append(line);

        if (firstStack.size() > 1)
            throw "bad 'on' symbol: cannot be inside any blocks.";

        QRegExp rx("^\\s*\\((.*)\\)$");
        rx.indexIn(line.mid(2));
        targetObjects = getObj(rx.cap(1).trimmed(), map);
        targetFlag = true;
        newBlock(true);
        return;
    }
    else if (line.startsWith("{"))
    {
        newBlock();
        return;
    }
    else if (line.startsWith("}"))
    {
        if (ifFlag == 2)
        {
            ifFlag = 0;
            head = tail = ifStack.pop();
            singleLine();
        }
        backBlock();
    }
    else if (line.startsWith("at"))
    {
        atList.append(line); // atList

        if (firstStack.size() > 1)
            throw "bad 'at' symbol: cannot be inside any blocks.";

        QRegExp rx("^\\s*\\((.*)\\)$");
        rx.indexIn(line.mid(2));
        int level = rx.cap(1).toInt();

        QString l;
        for (int i = 0; i < 11; i++)
        {
            while ((l = pIn->readLine().replace('\t', ' ').trimmed()).isEmpty())
                if (pIn->atEnd())
                    throw "bad <at> block: less than 11 lines";
            atList.append(l); // atList
            QStringList list = l.split(' ', QString::SkipEmptyParts);
            if (list.length() != 11)
                throw "bad <at> block: less than 11 components in one line";
            for (int j = 0; j < 11; j++)
            {
                QString ll = list.at(j);
                if (ll == "." || ll == "0") continue;
                QRegExp rx1("^(\\w*)?(#\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?([.]\\w*)?");
                rx1.indexIn(ll);
                QList<QString> c;
                for (int i = 3; i <= rx1.captureCount(); i++)
                    if (rx1.cap(i).startsWith("."))
                        c.append(rx1.cap(i).mid(1));
                MagicDisplayObject *ret = MagicHelper::createObject(rx1.cap(1), rx1.cap(2).mid(1), c, j, i, level, map);
                if (ret)
                    map->appendObject(ret);
            }
        }
        return;
    }
    else
    {
        head = tail = new MagicAssignment(processLine(line));
        //qDebug() << line << " => " << dynamic_cast<MagicAssignment *>(nowStack.top())->operand->getValue(NULL).getString() << endl;
    }

    // Processing single line;
    singleLine();
}

void MagicExpression::initAll()
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

    onList.clear(), atList.clear();
}

void lineInfo(QString line, QTextStream &in)
{
    qDebug() << "\t@line: -> " << line << "(" << in.readLine() << "," << in.readLine() << ")";
}

void lineInfo(QString line, QStringList::iterator i)
{
    qDebug() << "\t@line: -> " << line << "(" << *i++ << "," << *i++ << ")";
}

MagicExpression *MagicExpression::input(QString fileName, MagicMap *map)
{
    initAll();

    preprocessing = true;

    QRegExp rx("(.*/)");
    rx.indexIn(fileName);
    QString filepre = rx.cap(1);

    QFile *file = new QFile(fileName);
    map->setPath(filepre);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw "File Cannot Open...";

    QStack<QTextStream *> inStack;

    inStack.push(new QTextStream(file));
    while (!inStack.empty())
    {
    newFile:
        QTextStream &in = *inStack.top();
        while (!in.atEnd())
        {
            QString line = QString(in.readLine().split("//").at(0)).replace('\t', ' ').trimmed();


            if (line.isEmpty())
                continue;

            if (line.startsWith("#include "))
            {
                QString newFileName = filepre + line.mid(9).trimmed();
                QFile *newFile = new QFile(newFileName);
                if (!newFile->open(QIODevice::ReadOnly | QIODevice::Text))
                    throw QString("File <") + newFileName + "> Cannot Open...";
                inStack.push(new QTextStream(newFile));
                goto newFile;
            }

            if (targetFlag)
                onList.append(line);

            try
            {
                goForIt(line, map, &in);
            }
            catch (const char *e)
            {
                qDebug() << "Exception : " << e;
                lineInfo(line, in);
                return NULL;
            }
            catch (int x)
            {
                qDebug() << "Exception : " << x;
                lineInfo(line, in);
                return NULL;
            }
            catch (QString x)
            {
                qDebug() << x;
                lineInfo(line, in);
                return NULL;
            }
        }
        inStack.pop();
    }

    preprocessing = false;
    for (auto i = onList.begin(); i != onList.end(); i++)
    {
        try
        {
            goForIt(*i, map, NULL);
        }
        catch (const char *e)
        {
            qDebug() << "Exception : " << e;
            lineInfo(*i, i);
            return NULL;
        }
        catch (int x)
        {
            qDebug() << "Exception : " << x;
            lineInfo(*i, i);
            return NULL;
        }
        catch (QString x)
        {
            qDebug() << x;
            lineInfo(*i, i);
            return NULL;
        }
    }

    return final();
}

void MagicExpression::process(QTextStream &in, int n, MagicMap *map)
{
    initAll();

    preprocessing = false;

    for (int i = 0; i < n; i++)
    {
        QString line = QString(in.readLine().split("//").at(0)).replace('\t', ' ').trimmed();
        if (line.isEmpty())
            continue;

        if (targetFlag || line.startsWith("on")) // avoid the ignorance...>_<
            onList.append(line);

        try
        {
            if (line.startsWith("at"))
                i += 11;
            goForIt(line, map, &in);
        }
        catch (const char *e)
        {
            qDebug() << "Exception : " << e;
            lineInfo(line, in);
        }
        catch (int x)
        {
            qDebug() << "Exception : " << x;
            lineInfo(line, in);
        }
    }
}

MagicExpression *MagicExpression::final()
{
    head = tail = new MagicExpression();
    singleLine();

    for (auto i = gotoStack.top().begin(); i != gotoStack.top().end(); i++)
        (*i)->setNext(labelStack.top()[(*i)->label]->next);

    gotoStack.pop();
    labelStack.pop();
    nowStack.pop();
    return firstStack.pop();
}

MagicDisplayObject *MagicExpression::environment = NULL;

void MagicExpression::setEnvironment(MagicDisplayObject *environment)
{
    MagicExpression::environment = environment;
}
