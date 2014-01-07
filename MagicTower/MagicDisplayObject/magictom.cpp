#include "magictom.h"

#include <QBitmap>

QPixmap *MagicTom::Pix[4][3] = {  {new QPixmap(":/images/Tom_face1"), new QPixmap(":/images/Tom_face2"), new QPixmap(":/images/Tom_face")},
                                {new QPixmap(":/images/Tom_left1"), new QPixmap(":/images/Tom_left2"), new QPixmap(":/images/Tom_left")},
                                {new QPixmap(":/images/Tom_back1"), new QPixmap(":/images/Tom_back2"), new QPixmap(":/images/Tom_back")},
                                {new QPixmap(":/images/Tom_right1"), new QPixmap(":/images/Tom_right2"), new QPixmap(":/images/Tom_right")}};

MagicTom::MagicTom()
{
    pix = Pix[0][2];
    x = y = 0;
    mSound = new QSound(":/sounds/step");
    mBeep = new QSound(":/sounds/beep");
    animateState = -1;
}

void MagicTom::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}
/*
void MagicTom::moveTo(int tx, int ty)
{
    x = tx, y = ty;
}
*/
bool MagicTom::setStep(int direction)
{
    this->pix = this->Pix[direction][2];
    int dx[4]={0, -32, 0, 32}, dy[4]={32, 0, -32, 0};
    if (x + dx[direction] > 320 || y + dy[direction] > 320 || x + dx[direction] < 0 || y + dy[direction] < 0)
    {
        mBeep->play();
        return false;
    }
    else
    {
        mSound->play();
        return true;
    }
}
/*
bool MagicTom::move()
{
    x += dx, y += dy;
    return true;
}
*/

void MagicTom::change_pic(int direction, int duration)
{
    if(duration > 0)
        pix = Pix[direction][(duration / 4) % 2];
    else
        pix = Pix[direction][2];
}
