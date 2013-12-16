#ifndef MAGICBACKSOUND_H
#define MAGICBACKSOUND_H

#include "magicsoundobject.h"

#include <QtMultimedia/QSound>

class MagicBackSound : public MagicSoundObject
{
    QSound *mSound;

public:
    MagicBackSound();
    virtual void play(int = 0);
    virtual void stop();
};

#endif // MAGICBACKSOUND_H
