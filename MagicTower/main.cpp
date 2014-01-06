#include "mainwindow.h"
#include <QApplication>

#include "MagicExpression/magicexpression.h"

void test()
{
    printf("Hello test!\n");
    MagicExpression *k = MagicExpression::input(new QFile("/home/jimmy/Documents/MagicTower/MagicTower/map/test.txt"), NULL);
    delete k;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //test();

    return a.exec();
}
