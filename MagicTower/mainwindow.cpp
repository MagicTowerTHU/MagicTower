#include "mainwindow.h"
#include "widget.h"
#include "MagicAnimate/magicmessage.h"

#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QFileDialog>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Magic Tower"));

    createMenus();

    mWidget = new Widget(this);
    mStatus = new Status(mWidget->getMap(), this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mWidget, 0, 1);
    layout->addWidget(mStatus, 0, 0);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    QFontDatabase::addApplicationFont(":/fonts/微软雅黑");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), mWidget, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), mStatus, SLOT(animate()));
    timer->start(20);
}

void MainWindow::createMenus()
{
    openAct = new QAction(tr("Load &Map"), this);
    saveAct = new QAction(tr("&Save record"), this);
    loadAct = new QAction(tr("L&oad record"), this);
    exitAct = new QAction(tr("E&xit"), this);

    fileMenu = menuBar()->addMenu(tr("&Magic Tower"));
    fileMenu->addAction(openAct);
    openAct->setShortcut(QKeySequence("Ctrl+m"));
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    saveAct->setShortcut(QKeySequence("Ctrl+s"));
    fileMenu->addAction(loadAct);
    loadAct->setShortcut(QKeySequence("Ctrl+o"));
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    exitAct->setShortcut(QKeySequence("Ctrl+w"));

    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
    connect(loadAct, SIGNAL(triggered()), this, SLOT(load()));
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Magic Map++ (*.m++)"));
    mWidget->loadMap(filename);
}

void MainWindow::save()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Open File"), "save0.rec", tr("Magic Record (*.rec)"));
    if (filename.isEmpty())
        return;
    try
    {
        mWidget->saveRec(filename);
    }
    catch (const char *e)
    {
        mWidget->getMap()->appendAnimate(new MagicMessage(mWidget->getMap(), QString(e)), false);
    }
}

void MainWindow::load()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "save0.rec", tr("Magic Record (*.rec)"));
    if (filename.isEmpty())
        return;
    mWidget->loadRec(filename);
}

MagicMap *MainWindow::getMap()
{
    return mWidget->getMap();
}

Widget *MainWindow::getWidget()
{
    return mWidget;
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    mWidget->keyPressEvent(e);
}
