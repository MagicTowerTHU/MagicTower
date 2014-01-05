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

int MagicVarient::getInt()
{
    if(!this->type)
        return *((int*)this->data);
    else
    {
        throw("Error: Trying to get int value from string MagicVatirnt.");
        return NULL;
    }
}

QString MagicVarient::getString()
{
    if(this->type)
        return *((QString*)this->data);
    else
        return QString("<Number>") + QString::number(getInt());
}

bool MagicVarient::isTrue()
{
    if(this->type && *((QString*)this->data) != "") return true;
    if(!this->type && *((int*)this->data) != 0) return true;
    return false;
}

MagicVarient MagicVarient::operator==(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) == *(int*)(a.data);
        return temp;
    }
    if(this->type && a.type)
    {
        *((int*)temp.data) = *((QString*)(this->data)) == *((QString *)(a.data));
        return temp;
    }
    throw("Error: Invalid use of operator ==");
    return NULL;
}

MagicVarient MagicVarient::operator!=(MagicVarient a)
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
    return NULL;
}

MagicVarient MagicVarient::operator>(MagicVarient a)
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
    return NULL;
}

MagicVarient MagicVarient::operator>=(MagicVarient a)
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
    return NULL;
}

MagicVarient MagicVarient::operator<(MagicVarient a)
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
    return NULL;
}

MagicVarient MagicVarient::operator<=(MagicVarient a)
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
    return NULL;
}



MagicVarient MagicVarient:: operator+(MagicVarient a)
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
    return NULL;
}

MagicVarient MagicVarient::operator-(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) - *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator -");
    return NULL;
}

MagicVarient MagicVarient::operator*(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) * *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator *");
    return NULL;
}
MagicVarient MagicVarient::operator/(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) / *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator /");
    return NULL;
}
MagicVarient MagicVarient::operator%(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) % *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator %");
    return NULL;
}
MagicVarient MagicVarient::operator^(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) ^ *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator ^");
    return NULL;
}
MagicVarient MagicVarient::operator&(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) & *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator &");
    return NULL;
}

MagicVarient MagicVarient::operator<<(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) << *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator <<");
    return NULL;
}

MagicVarient MagicVarient::operator>>(MagicVarient a)
{
    MagicVarient temp(0);
    if(!this->type && !a.type)
    {
        *((int*)temp.data) = *((int*)(this->data)) >> *(int*)(a.data);
        return temp;
    }
    throw("Error: Invalid use of operator >>");
    return NULL;
}

MagicVarient MagicVarient::operator~()
{
    MagicVarient temp(0);
    if(!this->type)
    {
        *((int*)temp.data) = ~(*((int*)(this->data)));
        return temp;
    }
    throw("Error: Invalid use of operator ~");
    return NULL;
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

MagicVarient MagicVarient::input(QString source, int &i)
{
    if(source[i] >= '0' && source[i] <= '9')
    {
        int temp = 0;
        while(source[i] >= '0' && source[i] <= '9' && i < source.size())
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
}

