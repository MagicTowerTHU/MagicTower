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

    int getInt() const;
    QString getString() const;
    QString getOutput() const;
    static MagicVarient setInput(QString);
    bool isTrue() const;

    MagicVarient operator==(MagicVarient) const;
    MagicVarient operator!=(MagicVarient) const;
    MagicVarient operator>(MagicVarient) const;
    MagicVarient operator>=(MagicVarient) const;
    MagicVarient operator<(MagicVarient) const;
    MagicVarient operator<=(MagicVarient) const;

    MagicVarient operator+(MagicVarient) const;
    MagicVarient operator-(MagicVarient) const;
    MagicVarient operator*(MagicVarient) const;
    MagicVarient operator/(MagicVarient) const;
    MagicVarient operator%(MagicVarient) const;
    MagicVarient operator^(MagicVarient) const;
    MagicVarient operator&(MagicVarient) const;
    MagicVarient operator<<(MagicVarient) const;
    MagicVarient operator>>(MagicVarient) const;
    MagicVarient operator~() const;

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
