#include "magictom.h"

#include <QBitmap>
#include <QDebug>

QString Pix_string[4][3] = {  {":/images/Tom_face1", ":/images/Tom_face2", ":/images/Tom_face"},
                              {":/images/Tom_left1", ":/images/Tom_left2", ":/images/Tom_left"},
                              {":/images/Tom_back1", ":/images/Tom_back2", ":/images/Tom_back"},
                              {":/images/Tom_right1", ":/images/Tom_right2", ":/images/Tom_right"}};

MagicTom::MagicTom(int x, int y, int level)
    : MagicDisplayObject(x, y, level)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            Pix[i][j] = new QPixmap(Pix_string[i][j]);

    pix = Pix[0][2];

    property["label"] = "tom";
    property["attack"] = 50;
    property["defend"] = 50;
    property["health"] = 500;
    property["exp"] = 0;
    property["money"] = 0;
    property["id"] = "";

    qDebug() <<"Tom: "<< property["attack"].getInt() << property["defend"].getInt() << property["health"].getInt();
    qDebug() <<"Tom: "<< property["label"].getString() << property["level"].getInt() << property["id"].getString();
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
        QSound::play(":/sounds/beep");
        return false;
    }
    else
    {
        QSound::play(":/sounds/step");
        return true;
    }
}

bool MagicTom::move(MagicMap *)
{
    return true;
}

void MagicTom::changePic(int direction, int duration)
{
    if (duration > 0)
        pix = Pix[direction][(duration / 4) % 2];
    else
        pix = Pix[direction][2];
}


bool MagicTom::haveInventory(QString label)
{
    for (auto i = inventory.begin(); i != inventory.end(); i++)
        if ( ((**i)["label"] == MagicVarient(label)).isTrue() )
            return true;
    return false;
}

bool MagicTom::consumeInventory(QString label)
{
    for (auto i = inventory.begin(); i != inventory.end(); i++)
        if ( ((**i)["label"] == MagicVarient(label)).isTrue() )
        {
            i = inventory.erase(i);
            return true;
        }
    return false;
}

bool MagicTom::consumeInventory(QString label, int color)
{
    for (auto i = inventory.begin(); i != inventory.end(); i++)
        if ( ((**i)["label"] == MagicVarient(label)).isTrue() &&
             ((**i)["color"] == MagicVarient(color)).isTrue() )
        {
            i = inventory.erase(i);
            return true;
        }
    return false;
}
