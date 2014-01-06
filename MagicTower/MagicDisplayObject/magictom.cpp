#include "magictom.h"

#include <QBitmap>

MagicTom::MagicTom()
{
    pix_face = new QPixmap(":/images/Tom_face");
    pix_face->setMask(QBitmap(":/images/Tom_face_mask"));
    pix_face_move[0] = new QPixmap(":/images/Tom_face1");
    pix_face_move[1] = new QPixmap(":/images/Tom_face2");
    pix_back = new QPixmap(":/images/Tom_back");
    pix_back_move[0] = new QPixmap(":/images/Tom_back1");
    pix_back_move[1] = new QPixmap(":/images/Tom_back2");
    pix_right = new QPixmap(":/images/Tom_right");
    pix_right_move[0] = new QPixmap(":/images/Tom_right1");
    pix_right_move[1] = new QPixmap(":/images/Tom_right2");
    pix_left = new QPixmap(":/images/Tom_left");
    pix_left_move[0] = new QPixmap(":/images/Tom_left1");
    pix_left_move[1] = new QPixmap(":/images/Tom_left2");
    pix = pix_face;
    x = y = 0;
    mSound = new QSound(":/sounds/step");
    mBeep = new QSound(":/sounds/beep");
    animateState = -1;
}

void MagicTom::paint(QPainter *painter)
{
    painter->drawPixmap(x, y, *pix);
}

void MagicTom::moveTo(int tx, int ty)
{
    x = tx, y = ty;
}

bool MagicTom::setStep(int dx, int dy)
{
    if(dy > 0 && dx == 0) this->pix = this->pix_face;
    else if(dy < 0 && dx == 0) this->pix = this->pix_back;
    else if(dx > 0 && dy == 0) this->pix = this->pix_right;
    else if(dx < 0 && dy == 0) this->pix = this->pix_left;
    if (x + dx > 320 || y + dy > 320 || x + dx < 0 || y + dy < 0)
    {
        mBeep->play();
        this->dx = this->dy = 0;
        return false;
    }
    else
    {
        this->dx = dx, this->dy = dy;
        mSound->play();
        return true;
    }
}

int MagicTom::direction()
{
    if(dx > 0 && dy == 0) return 0;
    if(dx < 0 && dy == 0) return 1;
    if(dy > 0 && dx == 0) return 2;
    if(dy < 0 && dx == 0) return 3;
    else return 4;
}

bool MagicTom::move()
{
    x += dx, y += dy;
    return true;
}


void MagicTom::show()
{
    if(animateState == -1)
    {
        switch (this->direction()) {
        case 1: //going left
            pix = pix_left;
            break;
        case 0: //going right
            pix = pix_right;
            break;
        case 2: //going down
            pix = pix_face;
            break;
        case 3: //going up
            pix = pix_back;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (this->direction()) {
        case 1: //going left
            pix = pix_left_move[(animateState + 4)/4 % 2];
            break;
        case 0: //going right
            pix = pix_right_move[(animateState + 4)/4 % 2];
            break;
        case 2: //going down
            pix = pix_face_move[(animateState + 4)/4 % 2];
            break;
        case 3: //going up
            pix = pix_back_move[(animateState + 4)/4 % 2];
            break;
        default:
            break;
        }
    }
}
