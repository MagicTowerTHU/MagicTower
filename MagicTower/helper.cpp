
#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

Helper::Helper()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    painter->translate(250, 250);

    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);
    painter->rotate(elapsed * 0.030);

    qreal r = elapsed / 1000.0;
    int n = 30;
    for (int i = 0; i < n; ++i) {
        painter->rotate(30);
        qreal factor = (i + r) / n;
        qreal radius = 0 + 120.0 * factor;
        qreal circleRadius = 1 + factor * 20;
        painter->drawEllipse(QRectF(radius, -circleRadius,
                                    circleRadius * 2, circleRadius * 2));
    }
    painter->restore();

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-150, -50, 300, 100), Qt::AlignCenter, QStringLiteral("Hello Qt"));

    QPixmap pix("../assets/1.PNG");
    painter->drawPixmap(100, 100, pix);
    painter->drawPixmap(-100, -100, pix);
}
