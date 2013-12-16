#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helper.h"
#include "widget.h"
#include "magicbacksound.h"

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Widget *mWidget;
    MagicBackSound *mBackSound;

public:
    MainWindow(QWidget *parent = 0);
    Helper helper;
    QTimer *timer;

    ~MainWindow();
    void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
