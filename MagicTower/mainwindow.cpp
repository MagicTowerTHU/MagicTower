#include "mainwindow.h"
#include "widget.h"

#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>

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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), mWidget, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), mStatus, SLOT(animate()));
    timer->start(20);
}

void MainWindow::createMenus()
{
    newAct = new QAction(tr("&Action"), this);
    openAct = new QAction(tr("Action1"), this);
    saveAct = new QAction(tr("Action2"), this);
    printAct = new QAction(tr("Action3"), this);
    exitAct = new QAction(tr("Action"), this);
    undoAct = new QAction(tr("Action"), this);
    redoAct = new QAction(tr("Action"), this);
    cutAct = new QAction(tr("Action"), this);
    copyAct = new QAction(tr("Action"), this);
    pasteAct = new QAction(tr("Action"), this);
    boldAct = new QAction(tr("Action"), this);
    italicAct = new QAction(tr("Action"), this);
    leftAlignAct = new QAction(tr("Action"), this);
    rightAlignAct = new QAction(tr("Action"), this);
    justifyAct = new QAction(tr("Action"), this);
    centerAct = new QAction(tr("Action"), this);
    setLineSpacingAct = new QAction(tr("Action"), this);
    setParagraphSpacingAct = new QAction(tr("Action"), this);
    aboutAct = new QAction(tr("Action"), this);
    aboutQtAct = new QAction(tr("Action"), this);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);
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
