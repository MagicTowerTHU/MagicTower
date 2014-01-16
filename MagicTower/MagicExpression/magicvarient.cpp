#include "magicvarient.h"

#include <QString>

MagicVarient::MagicVarient(int data)
{
    this->data = new int(data);
    this->type = false;
}

MagicVarient::MagicVarient(QString data)
{
    this->data = new QString(data);
    this->type = true;
}

MagicVarient::MagicVarient()
{
    this->data = 0;
    this->type = false;
}

int MagicVarient::getInt() const
{
    if(!this->type)
        return *((int*)this->data);
    else
    {
        throw("Error: Trying to get int value from string MagicVatirnt.");
        return 0;
    }
}

QString MagicVarient::getString() const
{
    if(this->type)
        return *((QString*)this->data);
    else
        return QString("<Number>") + QString::number(getInt());
}

QString MagicVarient::getOutput() const
{
    if (!this->data)
        return "\"";
    if (this->type)
        return "\"" + *((QString*)this->data);
    else
        return QString::number(getInt());
}

MagicVarient MagicVarient::setInput(QString t)
{
    if (t.startsWith("\""))
        return MagicVarient(t.mid(1));
    return MagicVarient(t.toInt());
}

bool MagicVarient::isTrue() const
{
    if(this->type && *((QString*)this->data) != "") return true;
    if(!this->type && *((int*)this->data) != 0) return true;
    return false;
}

MagicVarient MagicVarient::operator==(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) == *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        *((int *)temp.data) = *((QString *)(this->data)) == *((QString *)(a.data));
        return temp;
    }
    return MagicVarient(-1);
}

MagicVarient MagicVarient::operator!=(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) != *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        *((int*)temp.data) = *((QString*)(this->data)) != *((QString *)(a.data));
        return temp;
    }
    throw("Error: Invalid use of operator !=");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator>(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) > *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        *((int*)temp.data) = *((QString*)(this->data)) > *((QString *)(a.data));
        return temp;
    }
    throw("Error: Invalid use of operator >");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator>=(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) >= *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        *((int*)temp.data) = *((QString*)(this->data)) >= *((QString *)(a.data));
        return temp;
    }
    throw("Error: Invalid use of operator >=");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator<(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) < *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        *((int*)temp.data) = *((QString*)(this->data)) < *((QString *)(a.data));
        return temp;
    }
    throw("Error: Invalid use of operator <");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator<=(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) <= *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        *((int*)temp.data) = *((QString*)(this->data)) <= *((QString *)(a.data));
        return temp;
    }
    throw("Error: Invalid use of operator <=");
    return MagicVarient(0);
}



MagicVarient MagicVarient:: operator+(MagicVarient a) const
{
    if(!this->type && !a.type)
    {
        MagicVarient temp(0);
        *((int*)temp.data) = *((int*)(this->data)) + *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        MagicVarient temp("");
        *((QString*)temp.data) = *((QString*)(this->data)) + *((QString *)(a.data));
        return temp;
    }
    throw("Error: Invalid use of operator +");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator-(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) - *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator -");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator*(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) * *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator *");
    return MagicVarient(0);
}
MagicVarient MagicVarient::operator/(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) / *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator /");
    return MagicVarient(0);
}
MagicVarient MagicVarient::operator%(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) % *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator %");
    return MagicVarient(0);
}
MagicVarient MagicVarient::operator^(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) ^ *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator ^");
    return MagicVarient(0);
}
MagicVarient MagicVarient::operator&(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) & *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator &");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator<<(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) << *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator <<");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator>>(MagicVarient a) const
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) >> *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator >>");
    return MagicVarient(0);
}

MagicVarient MagicVarient::operator~() const
{
    MagicVarient temp(0);
    if(!this->type)
    {
        *((int*)temp.data) = ~(*((int*)(this->data)));
        return temp;
    }
    throw("Error: Invalid use of operator ~");
    return MagicVarient(0);
}

MagicVarient & MagicVarient::operator+=(MagicVarient a)
{
    return *this = *this + a;
}

MagicVarient & MagicVarient::operator-=(MagicVarient a)
{
    return *this = *this - a;
}

MagicVarient & MagicVarient::operator*=(MagicVarient a)
{
    return *this = *this * a;
}
MagicVarient & MagicVarient::operator/=(MagicVarient a)
{
    return *this = *this / a;
}
MagicVarient & MagicVarient::operator%=(MagicVarient a)
{
    return *this = *this % a;
}

MagicVarient MagicVarient::operator=(int x)
{
    type = false;
    data = new int(x);
    return *this;
}

MagicVarient MagicVarient::operator=(QString x)
{
    type = true;
    data = new QString(x);
    return *this;
}

MagicVarient MagicVarient::input(QString source, int &i)
{
    if (source[i] >= '0' && source[i] <= '9')
    {
        int temp = 0;
        while (source[i] >= '0' && source[i] <= '9' && i < source.size())
        {
            temp *= 10;
            temp += source[i].digitValue();
            i++;
        }
        return MagicVarient(temp);
    }
    else if (source[i] == '\"')
    {
        QString temp("");
        while (++i < source.size() && source[i] != '\"')
            temp += source[i];
        if (i++ == source.size())
            throw("Error: input reaches data end!");
        return MagicVarient(temp);
    }
    throw "Invalid number or string...";
}
