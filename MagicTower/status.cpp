#include "status.h"

#include <QDebug>

Status::Status(MagicMap *map, QWidget *parent) :
    QWidget(parent)
{
    mMap = map;
    setFixedSize(120, 400);
}

void Status::animate()
{
    repaint();
}

void Status::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setFont(QFont("黑体", 15));

    painter.drawText(0, 20, QString("MagicTom"));
    painter.drawText(0, 60, QString("生命: ") + QString::number((*mMap->Tom())["health"].getInt()));
    painter.drawText(0, 90, QString("攻击: ") + QString::number((*mMap->Tom())["attack"].getInt()));
    painter.drawText(0, 120, QString("防御: ") + QString::number((*mMap->Tom())["defend"].getInt()));
    painter.drawText(0, 150, QString("层数: ") + QString::number((*mMap->Tom())["level"].getInt()));
    painter.drawText(0, 180, QString("经验: ") + QString::number((*mMap->Tom())["exp"].getInt()));
    painter.drawText(0, 210, QString("金钱: ") + QString::number((*mMap->Tom())["money"].getInt()));

    painter.end();
}
