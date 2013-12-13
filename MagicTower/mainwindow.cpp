#include "mainwindow.h"
#include "widget.h"

#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Magic Tower"));

    mWidget = new Widget(&helper, this);
    QLabel *nativeLabel = new QLabel(tr("Native"));
    nativeLabel->setAlignment(Qt::AlignHCenter);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mWidget, 0, 0);
    layout->addWidget(nativeLabel, 1, 0);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), mWidget, SLOT(animate()));
    timer->start(30);
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    mWidget->keyPressEvent(e);
}
