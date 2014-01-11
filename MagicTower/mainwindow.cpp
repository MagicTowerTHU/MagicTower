#include "mainwindow.h"
#include "widget.h"

#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Magic Tower"));

    mWidget = new Widget(this);
    mStatus = new Status(mWidget->getMap(), this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mWidget, 0, 1);
    layout->addWidget(mStatus, 0, 0);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), mWidget, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), mStatus, SLOT(animate()));
    timer->start(20);
}

MagicMap *MainWindow::getMap()
{
    return mWidget->getMap();
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    mWidget->keyPressEvent(e);
}
