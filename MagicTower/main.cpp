#include "mainwindow.h"
#include <QApplication>

#include "MagicExpression/magicexpression.h"

void test()
{
    printf("Hello test!\n");
    MagicExpression *k = MagicExpression::input(new QFile("D:\\SkyDrive\\Assignments\\de_UTF8\\MagitTower\\MagicTower\\map\\test.txt"));
    delete k;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    test();

    return a.exec();
}
