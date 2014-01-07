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
    //animateState = -1;
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

bool MagicTom::move(MagicMap *)
{
    return true;
}

/*
int MagicTom::direction()
{
    if(dx > 0 && dy == 0) return 0;
    if(dx < 0 && dy == 0) return 1;
    if(dy > 0 && dx == 0) return 2;
    if(dy < 0 && dx == 0) return 3;
    else return 4;
}

bool MagicTom::move(MagicMap *map)
>>>>>>> 759716628e3561813d36e7d64d08d8d3740ddfbd
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
