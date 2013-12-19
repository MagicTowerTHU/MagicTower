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

    bool operator==(const MagicVarient &);
    bool operator!=(const MagicVarient &);
    bool operator>(const MagicVarient &);
    bool operator>=(const MagicVarient &);
    bool operator<(const MagicVarient &);
    bool operator<=(const MagicVarient &);

    MagicVarient &operator+(const MagicVarient &);
    MagicVarient &operator-(const MagicVarient &);
    MagicVarient &operator*(const MagicVarient &);
    MagicVarient &operator/(const MagicVarient &);
    MagicVarient &operator%(const MagicVarient &);
    MagicVarient &operator^(const MagicVarient &);
    MagicVarient &operator&(const MagicVarient &);
    MagicVarient &operator<<(const MagicVarient &);
    MagicVarient &operator>>(const MagicVarient &);
    MagicVarient &operator~();
};

#endif // MAGICVARIENT_H
