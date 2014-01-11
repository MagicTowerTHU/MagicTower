#ifndef STATUS_H
#define STATUS_H

#include "magicmap.h"

#include <QWidget>

class Status : public QWidget
{
    Q_OBJECT
public:
    explicit Status(MagicMap *, QWidget *parent = 0);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    MagicMap *mMap;

};

#endif // STATUS_H
