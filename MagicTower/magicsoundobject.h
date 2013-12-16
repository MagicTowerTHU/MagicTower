#ifndef MAGICSOUNDOBJECT_H
#define MAGICSOUNDOBJECT_H

#include "magicobject.h"

class MagicSoundObject : public MagicObject
{
public:
    MagicSoundObject();
    virtual void play(int = 0) = 0;
    virtual void stop() = 0;
};

#endif // MAGICSOUNDOBJECT_H
