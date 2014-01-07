#include "mainwindow.h"
#include <QApplication>

#include "MagicExpression/magicexpression.h"

void test(MainWindow *pW)
{
    printf("Hello test!\n");
    MagicExpression *k = MagicExpression::input(new QFile(":/maps/test"), pW->getMap());
    k->run(pW->getMap());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    test(&w);

    return a.exec();
}
