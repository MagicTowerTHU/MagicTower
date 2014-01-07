#ifndef MAGICVARIENT_H
#define MAGICVARIENT_H

#include <QString>

class MagicVarient
{
    bool type;
    void *data;

public:
    MagicVarient(int);
    MagicVarient(QString);
    MagicVarient();

    int getInt();
    QString getString();
    bool isTrue();

    MagicVarient operator==(MagicVarient);
    MagicVarient operator!=(MagicVarient);
    MagicVarient operator>(MagicVarient);
    MagicVarient operator>=(MagicVarient);
    MagicVarient operator<(MagicVarient);
    MagicVarient operator<=(MagicVarient);

    MagicVarient operator+(MagicVarient);
    MagicVarient operator-(MagicVarient);
    MagicVarient operator*(MagicVarient);
    MagicVarient operator/(MagicVarient);
    MagicVarient operator%(MagicVarient);
    MagicVarient operator^(MagicVarient);
    MagicVarient operator&(MagicVarient);
    MagicVarient operator<<(MagicVarient);
    MagicVarient operator>>(MagicVarient);
    MagicVarient operator~();

    MagicVarient &operator+=(MagicVarient);
    MagicVarient &operator-=(MagicVarient);
    MagicVarient &operator*=(MagicVarient);
    MagicVarient &operator/=(MagicVarient);
    MagicVarient &operator%=(MagicVarient);

    MagicVarient operator=(int);
    MagicVarient operator=(QString);

    static MagicVarient input(QString, int &);
};


#endif // MAGICVARIENT_H
