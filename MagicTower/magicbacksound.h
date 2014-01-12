#ifndef MAGICBACKSOUND_H
#define MAGICBACKSOUND_H

#include "magicsoundobject.h"

#include <QtMultimedia/QSound>

class MagicBackSound : public MagicSoundObject
{
    QSound *mSound[5];
    int now;

public:
    MagicBackSound();
    virtual void play(int = 0);
    virtual void stop();
    void change(int);
};

#endif // MAGICBACKSOUND_H
