#include "status.h"

#include <QDebug>

Status::Status(MagicMap *map, QWidget *parent) :
    QWidget(parent)
{
    mMap = map;
    setFixedSize(150, 400);
}

void Status::animate()
{
    repaint();
}

void Status::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawText(0, 30, QString("MagicTom"));
    painter.drawText(0, 60, QString("Health: ") + QString::number((*mMap->Tom())["health"].getInt()));
    painter.drawText(0, 90, QString("Attack: ") + QString::number((*mMap->Tom())["attack"].getInt()));
    painter.drawText(0, 120, QString("Defend: ") + QString::number((*mMap->Tom())["defend"].getInt()));
    painter.drawText(0, 150, QString("Level: ") + QString::number((*mMap->Tom())["level"].getInt()));

    painter.end();
}
