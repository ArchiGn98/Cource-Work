#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //TODO: добавить кнопку печать отчета в админа, печать использует кореллированные запросы
}
