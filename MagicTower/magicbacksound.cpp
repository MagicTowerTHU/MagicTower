#include "magicbacksound.h"

MagicBackSound::MagicBackSound()
{
    mSound = new QSound(":/sounds/858.wav");
}

void MagicBackSound::play(int loop) // default: 0
{
    if (loop < 0) loop = 2147483647; // wtf
    mSound->setLoops(loop);
    mSound->play();
}

void MagicBackSound::stop()
{
    mSound->stop();
}
