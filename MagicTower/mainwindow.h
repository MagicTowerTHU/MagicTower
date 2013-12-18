#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widget.h"
#include "magicbacksound.h"

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Widget *mWidget;

public:
    MainWindow(QWidget *parent = 0);
    QTimer *timer;

    ~MainWindow();
    void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
