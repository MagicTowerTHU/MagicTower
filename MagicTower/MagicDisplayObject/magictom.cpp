#include "magictom.h"

#include <QBitmap>

QString Pix_string[4][3] = {  {":/images/Tom_face1", ":/images/Tom_face2", ":/images/Tom_face"},
                                {":/images/Tom_left1", ":/images/Tom_left2", ":/images/Tom_left"},
                                {":/images/Tom_back1", ":/images/Tom_back2", ":/images/Tom_back"},
                                {":/images/Tom_right1", ":/images/Tom_right2", ":/images/Tom_right"}};

MagicTom::MagicTom()
{
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            Pix[i][j] = new QPixmap(Pix_string[i][j]);

    pix = Pix[0][2];

    property["label"] = "tom";

    x = y = 0;
    mSound = new QSound(":/sounds/step");
    mBeep = new QSound(":/sounds/beep");
}

void MagicTom::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

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

bool MagicTom::move(MagicMap *)
{
    return true;
}


void MagicTom::change_pic(int direction, int duration)
{
    if(duration > 0)
        pix = Pix[direction][(duration / 4) % 2];
    else
        pix = Pix[direction][2];
}
