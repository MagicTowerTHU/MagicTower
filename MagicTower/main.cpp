#include "mainwindow.h"
#include <QApplication>

#include "MagicExpression/magicexpression.h"

void test(MainWindow *pW)
{
    printf("Hello test!\n");
    pW->getWidget()->loadMap(":/maps/test");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    test(&w);

    return a.exec();
}
