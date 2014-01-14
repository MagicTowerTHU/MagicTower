#include "magicbacksound.h"

MagicBackSound::MagicBackSound()
{
    mSound[0] = new QSound(":/sounds/back_0");
    mSound[1] = new QSound(":/sounds/back_1");
    mSound[2] = new QSound(":/sounds/back_2");
    mSound[3] = new QSound(":/sounds/back_3");
    mSound[4] = new QSound(":/sounds/back_4");
    now = 1;
}

void MagicBackSound::play(int loop) // default: 0
{
    if (loop <= 0) loop = 2147483647; // wtf
    mSound[now]->play();
    mSound[now]->setLoops(loop);
}

void MagicBackSound::change(int target)
{
    soundMutex.lock();
    if (now != target)
    {
        stop();
        now = target;
        if (target >= 0 && target <= 4)
            play();
    }
    soundMutex.unlock();
}

void MagicBackSound::stop()
{
    try
    {
        if (now >= 0 && now <= 4)
        mSound[now]->stop();
    }
    catch (...) {}
}
