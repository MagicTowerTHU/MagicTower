#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widget.h"
#include "magicbacksound.h"
#include "magicmap.h"
#include "status.h"

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Widget *mWidget;
    Status *mStatus;

    void createMenus();
    QMenu *fileMenu;

    QAction *openAct;
    QAction *saveAct;
    QAction *loadAct;
    QAction *exitAct;

private slots:
    void open();
    void save();
    void load();

public:
    MainWindow(QWidget *parent = 0);
    QTimer *timer;
    MagicMap *getMap();
    Widget *getWidget();

    ~MainWindow();
    void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
